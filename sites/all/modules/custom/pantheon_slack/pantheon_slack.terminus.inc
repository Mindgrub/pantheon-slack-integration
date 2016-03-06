<?php

/**
 * @file
 * Terminus integration for Pantheon Slack module.
 */


use Terminus\Models\Auth;
use Terminus\Models\Collections\Sites;

/**
 * Callback for auth command from Slack.
 *
 * @param array $args
 * @return bool
 */
function _pantheon_slack_terminus_auth($args = []) {
  $is_authenticated = _pantheon_slack_terminus_authenticate_user_by_token($args[0]);

  if ($is_authenticated) {
    // @TODO -- Does this user exist already?
    $entity = entity_create('pantheon_slack_user', array('type' => 'pantheon_slack_user'));
    $wrapper = entity_metadata_wrapper('pantheon_slack_user', $entity);
    $wrapper->field_slack_team_id->set($_POST['team_id']);
    $wrapper->field_slack_team_domain->set($_POST['team_domain']);
    $wrapper->field_slack_user_id->set($_POST['user_id']);
    $wrapper->field_slack_user_name->set($_POST['user_name']);
    $wrapper->field_pantheon_machine_token->set($args[0]);
    $wrapper->save();

    echo "You've successfully connected your Slack account with Pantheon.";
  } else {
    echo "There was an error connecting your Slack account with Pantheon.  Please double check your machine token and try again.";
  }

  return $is_authenticated;
}

/**
 * Helper function ot authenticate a user to Pantheon by their Machine Token.
 *
 * @param $token
 * @return bool
 */
function _pantheon_slack_terminus_authenticate_user_by_token($token) {
  $auth = new Auth();
  try {
    $auth_args = [
      'token' => $token,
    ];
    $is_authenticated = $auth->logInViaMachineToken($auth_args);
  } catch (\Terminus\Exceptions\TerminusException $e) {
    $is_authenticated = FALSE;
  }
  return $is_authenticated;
}

/**
 * Helper function to authenticate users based on their stored machine token.
 * This way users only need to authenticate once and they continue to work.
 * To remove someone, just revoke their machine token.
 *
 * @param $user_id
 * @return bool
 */
function _pantheon_slack_terminus_authenticate_user_by_id($user_id) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'pantheon_slack_user')
    ->propertyCondition('type', 'pantheon_slack_user')
    ->fieldCondition('field_slack_user_id', 'value', $user_id)
    ->range(0, 1);

  $results = $query->execute();

  if (!empty($results['pantheon_slack_user'])) {
    $wrapper = entity_metadata_wrapper('pantheon_slack_user', key($results['pantheon_slack_user']));
    return _pantheon_slack_terminus_authenticate_user_by_token($wrapper->field_pantheon_machine_token->value());
  }

  return FALSE;
}

function _pantheon_slack_terminus_sites() {
  if (_pantheon_slack_terminus_authenticate_user_by_id($_POST['user_id'])) {
    $sites = new Sites();
    $user_sites = $sites->all();
    var_dump($user_sites);
  } else {
    echo "FAIL";
  }
}