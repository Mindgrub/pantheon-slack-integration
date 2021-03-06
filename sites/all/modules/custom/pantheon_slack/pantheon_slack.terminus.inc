<?php

/**
 * @file
 * Terminus integration for Pantheon Slack module.
 */


use Terminus\Models\Auth;
use Terminus\Models\Collections\Sites;
use Terminus\Models\Collections\Environments;

/**
 * Callback for auth command from Slack.
 *
 * @param array $args
 * @return bool
 */
function _pantheon_slack_terminus_auth($args = []) {
  if (count($args) < 1) {
    _pantheon_slack_send_output_to_slack(t('Invalid number of arguments.  `/pantheon auth <machine-token>`'));
    return FALSE;
  }
  $is_authenticated = _pantheon_slack_terminus_authenticate_user_by_token($args[0]);

  if ($is_authenticated) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'pantheon_slack_user')
      ->propertyCondition('type', 'pantheon_slack_user')
      ->fieldCondition('field_slack_team_id', 'value', $_POST['team_id'])
      ->fieldCondition('field_slack_user_id', 'value', $_POST['user_id'])
      ->range(0, 1);

    $result = $query->execute();
    if (!empty($result['pantheon_slack_user'])) {
      $wrapper = entity_metadata_wrapper('pantheon_slack_user', key($result['pantheon_slack_user']));
    } else {
      $entity = entity_create('pantheon_slack_user', array('type' => 'pantheon_slack_user'));
      $wrapper = entity_metadata_wrapper('pantheon_slack_user', $entity);
    }
    $wrapper->field_slack_team_id->set($_POST['team_id']);
    $wrapper->field_slack_team_domain->set($_POST['team_domain']);
    $wrapper->field_slack_user_id->set($_POST['user_id']);
    $wrapper->field_slack_user_name->set($_POST['user_name']);
    $wrapper->field_pantheon_machine_token->set($args[0]);
    $wrapper->save();

    _pantheon_slack_send_output_to_slack(t("You've successfully connected your Slack account with Pantheon."));
  } else {
    _pantheon_slack_send_output_to_slack(t("There was an error connecting your Slack account with Pantheon.  Please double check your machine token and try again."));
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

/**
 * Retrieve a user's sites from Pantheon and print them for display in Slack.
 */
function _pantheon_slack_terminus_sites() {
  if (_pantheon_slack_terminus_authenticate_user_by_id($_POST['user_id'])) {
    $sites = new Sites();
    $user_sites = $sites->all();
    $site_names = [];
    foreach ($user_sites as $site) {
      $site_names[] = $site->get('name');
    }
    _pantheon_slack_send_output_to_slack(implode("\n", $site_names));
  } else {
    _pantheon_slack_send_output_to_slack(t("Failure authenticating to Pantheon.  Try running `/pantheon help` for details about authenticating."));
  }
}

/**
 * Set's a default Pantheon site for a channel to make things easier for future
 * commands.
 *
 * @param array $args
 */
function _pantheon_slack_terminus_set_channel_default($args = []) {
  if (count($args) < 1) {
    _pantheon_slack_send_output_to_slack(t('Invalid number of arguments.  `/pantheon set-channel-default <site-name>`'));
    return;
  }
  $site_name = array_shift($args);
  // We don't care whether the site name is valid or not.  Maybe the person adding
  // it doesn't have access to the site for whatever reason.
  if ($existing = _pantheon_slack_terminus_lookup_channel($_POST['channel_id'])) {
    $existing->field_pantheon_site_name->set($site_name);
    $existing->save();
  } else {
    $entity = entity_create('pantheon_slack_channel', array('type' => 'pantheon_slack_channel'));
    $wrapper = entity_metadata_wrapper('pantheon_slack_channel', $entity);
    $wrapper->field_slack_team_id->set($_POST['team_id']);
    $wrapper->field_slack_team_domain->set($_POST['team_domain']);
    $wrapper->field_slack_channel_id->set($_POST['channel_id']);
    $wrapper->field_slack_channel_name->set($_POST['channel_name']);
    $wrapper->field_pantheon_site_name->set($site_name);
    $wrapper->save();
  }

  _pantheon_slack_send_output_to_slack(t('Set site @site as default for channel @channel', array('@site' => $site_name, '@channel' => $_POST['channel_name'])));
}

/**
 * Tells Slack what the default Pantheon site is for a channel.
 */
function _pantheon_slack_terminus_get_channel_default() {
  if ($existing = _pantheon_slack_terminus_lookup_channel($_POST['channel_id'])) {
    _pantheon_slack_send_output_to_slack(t('Default site for @channel is @site', array('@channel' => $_POST['channel_name'], '@site' => $existing->field_pantheon_site_name->value())));
  } else {
    _pantheon_slack_send_output_to_slack(t('There is no default site set for this channel.'));
  }
}

/**
 * Looks a Slack channel up in the database.
 *
 * @param string $channel_id
 * @return bool|\EntityMetadataWrapper
 */
function _pantheon_slack_terminus_lookup_channel($channel_id) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'pantheon_slack_channel')
    ->propertyCondition('type', 'pantheon_slack_channel')
    ->fieldCondition('field_slack_channel_id', 'value', $channel_id)
    ->range(0, 1);

  $results = $query->execute();

  if (!empty($results['pantheon_slack_channel'])) {
    return entity_metadata_wrapper('pantheon_slack_channel', key($results['pantheon_slack_channel']));
  }

  return FALSE;
}

/**
 * Deploy a channel's default site to the specified environment.
 *
 * @param array $args
 */
function _pantheon_slack_terminus_deploy_default_site($args = []) {
  if ($existing = _pantheon_slack_terminus_lookup_channel($_POST['channel_id'])) {
    $site_name = $existing->field_pantheon_site_name->value();
    if (count($args) < 1) {
      _pantheon_slack_send_output_to_slack(t('Invalid number of arguments.  `/pantheon deploy <environment>`'));
      return;
    }
    $env = array_shift($args);
    _pantheon_slack_terminus_deploy_site($site_name, $env);
  } else {
    _pantheon_slack_send_output_to_slack(t('There is no default site set for this channel.'));
  }
}

/**
 * Deploy a specific site on Pantheon to the specified environment.
 *
 * @param array $args
 */
function _pantheon_slack_terminus_deploy_specific_site($args = []) {
  if (count($args) <2) {
    _pantheon_slack_send_output_to_slack(t('Invalid number of arguments.  `/pantheon deploy-site <site-name> <environment>`'));
  } else {
    $site_name = array_shift($args);
    $env = array_shift($args);
    _pantheon_slack_terminus_deploy_site($site_name, $env);
  }
}

/**
 * Integration with Pantheon to deploy code for a particular environment of a
 * particular site.
 *
 * @param $site_name
 * @param $env
 */
function _pantheon_slack_terminus_deploy_site($site_name, $env) {
  if (_pantheon_slack_terminus_authenticate_user_by_id($_POST['user_id'])) {
    try {
      $sites = new Sites();
      $site = $sites->get($site_name);
      $environments = new Environments(['site' => $site]);
      if (!in_array($env, array('test', 'live'))) {
        _pantheon_slack_send_output_to_slack(t('You can only deploy to the test or live environment.'));
        return;
      }
      $environment = $environments->get($env);
      if (!$environment || !in_array($environment->get('id'), array('test', 'live'))) {
        _pantheon_slack_send_output_to_slack(t('You can only deploy to the test or live environment.'));
        return;
      }
      if (!$environment->hasDeployableCode()) {
        _pantheon_slack_send_output_to_slack(t('There is nothing to deploy.'));
        return;
      }
      $params = array(
        'updatedb'       => TRUE,
        'clear_cache'    => TRUE,
        'annotation'     => t('Deployed via Slack by user @user_name.', array('@user_name' => $_POST['user_name'])),
      );
      _pantheon_slack_send_output_to_slack(t("Deployment initiated for @site by <@@user>", array('@site' => $site_name, '@user' => $_POST['user_id'])), TRUE, FALSE);
      $workflow = $environment->deploy($params);
      $workflow->wait();
      $message = _pantheon_slack_get_workflow_output($workflow, ['failure' => 'Deployment failed.']);
      _pantheon_slack_send_output_to_slack($message, TRUE);
    } catch (\Terminus\Exceptions\TerminusException $e) {
      _pantheon_slack_send_output_to_slack(t("There was an error triggering your deployment."));
    }
  } else {
    _pantheon_slack_send_output_to_slack(t("Failure authenticating to Pantheon.  Try running `/pantheon help` for details about authenticating."));
  }
}

/**
 * Sends messages to Slack using the callback URL provided in the initial
 * request.
 *
 * @param $message
 * @param bool $visible_to_all
 */
function _pantheon_slack_send_output_to_slack($message, $visible_to_all = FALSE, $escape = TRUE) {
  $callback_url = $_POST['response_url'];

  if ($escape) {
    $message = str_replace(array('&', '<', '>'), array('&amp;', '&lt;', '&gt;'), $message);
  }

  $output = [
    'response_type' => $visible_to_all ? 'in_channel' : 'ephemeral',
    'text' => $message,
  ];

  if (variable_get('pantheon_slack_enable_output_debug', FALSE)) {
    echo $message;
  } else {
    drupal_http_request($callback_url, [
      'method' => 'POST',
      'data' => drupal_json_encode($output),
    ]);
  }
}

/**
 * A modified version of TerminusCommand/workflowOutput to allow us to send
 * messages from the workflow back to Slack.
 *
 * @param $workflow
 * @param array $messages
 * @return string
 */
function _pantheon_slack_get_workflow_output($workflow, array $messages = []) {
  if ($workflow->get('result') == 'succeeded') {
    $message = $workflow->get('active_description');
    if (isset($messages['success'])) {
      $message = $messages['success'];
    }
  } else {
    $message = 'Workflow failed.';
    if (isset($messages['failure'])) {
      $message = $messages['failure'];
    } elseif (!is_null($final_task = $workflow->get('final_task'))) {
      $message = $final_task->reason;
    }
  }
  return $message;
}