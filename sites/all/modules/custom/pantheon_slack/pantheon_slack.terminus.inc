<?php

/**
 * @file
 * Terminus integration for Pantheon Slack module.
 */

function _pantheon_slack_terminus_auth() {
  $terminus = new Terminus();
  return "Hello";
}