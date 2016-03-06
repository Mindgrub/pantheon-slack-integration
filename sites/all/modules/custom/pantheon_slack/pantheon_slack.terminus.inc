<?php

/**
 * @file
 * Terminus integration for Pantheon Slack module.
 */


use Terminus\Models\Auth;

function _pantheon_slack_terminus_auth() {

  $auth = new Auth();
  var_dump("HERE");
  var_dump($auth);
  return "Hello";
}