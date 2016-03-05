<?php

/**
 * Page callback for incoming requests made by Slack.
 *
 * @return string
 */
function pantheon_slack_slack_callback() {
  dpm(func_get_args());
  dpm($_POST);
  return "Hello";
}
