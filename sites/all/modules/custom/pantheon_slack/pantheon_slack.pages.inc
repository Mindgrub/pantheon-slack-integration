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
          echo 'CHANNEL DEFAULT';
          break;

        case 'deploy':
          echo 'DEPLOY';
          break;

        default:
          echo 'HELP';
      }
    }
  }
  watchdog("DEBUG", print_r($_POST, TRUE));
  drupal_exit();
}
