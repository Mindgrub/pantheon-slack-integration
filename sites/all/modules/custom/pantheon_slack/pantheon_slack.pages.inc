<?php

/**
 * Page callback for incoming requests made by Slack.
 *
 * @return string
 */
function pantheon_slack_slack_callback() {
  if (!isset($_POST['token']) || $_POST['token'] != variable_get('slack_slash_command_token', '')) {
    echo "Invalid request.  Is the Slack token set correctly?";
  } else {
    $command_args = explode(' ', $_POST['text']);
    if (!isset($command_args[0])) {
      echo "Invalid request.  Include sub-command";
    } else {
      $cache_uri = 'temporary://terminus/cache/' . $_POST['user_id'];
      file_prepare_directory($cache_uri, FILE_CREATE_DIRECTORY);
      $cache_path = drupal_realpath($cache_uri);
      putenv('TERMINUS_CACHE_DIR=' . $cache_path);
      module_load_include('inc', 'pantheon_slack', 'pantheon_slack.terminus');
      $command = array_shift($command_args);
      switch ($command) {
        case 'auth':
          _pantheon_slack_terminus_auth($command_args);
          break;

        case 'sites':
          _pantheon_slack_terminus_sites();
          break;

        case 'set-channel-default':
          _pantheon_slack_terminus_set_channel_default($command_args);
          break;

        case 'get-channel-default':
          _pantheon_slack_terminus_get_channel_default();
          break;

        case 'deploy':
          _pantheon_slack_terminus_deploy_default_site($command_args);
          break;

        case 'deploy-site':
          _pantheon_slack_terminus_deploy_specific_site($command_args);
          break;

        default:
          echo 'HELP';
      }
    }
  }
  watchdog("DEBUG", print_r($_POST, TRUE));
  drupal_exit();
}
