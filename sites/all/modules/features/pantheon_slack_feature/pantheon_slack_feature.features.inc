<?php
/**
 * @file
 * pantheon_slack_feature.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function pantheon_slack_feature_eck_bundle_info() {
  $items = array(
    'pantheon_slack_channel_pantheon_slack_channel' => array(
      'machine_name' => 'pantheon_slack_channel_pantheon_slack_channel',
      'entity_type' => 'pantheon_slack_channel',
      'name' => 'pantheon_slack_channel',
      'label' => 'Pantheon Slack Channel',
      'config' => array(),
    ),
    'pantheon_slack_user_pantheon_slack_user' => array(
      'machine_name' => 'pantheon_slack_user_pantheon_slack_user',
      'entity_type' => 'pantheon_slack_user',
      'name' => 'pantheon_slack_user',
      'label' => 'Pantheon Slack User',
      'config' => array(),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function pantheon_slack_feature_eck_entity_type_info() {
  $items = array(
    'pantheon_slack_channel' => array(
      'name' => 'pantheon_slack_channel',
      'label' => 'Pantheon Slack Channel',
      'properties' => array(
        'created' => array(
          'label' => 'Created',
          'type' => 'integer',
          'behavior' => 'created',
        ),
        'changed' => array(
          'label' => 'Changed',
          'type' => 'integer',
          'behavior' => 'changed',
        ),
      ),
    ),
    'pantheon_slack_user' => array(
      'name' => 'pantheon_slack_user',
      'label' => 'Pantheon Slack User',
      'properties' => array(
        'created' => array(
          'label' => 'Created',
          'type' => 'integer',
          'behavior' => 'created',
        ),
        'changed' => array(
          'label' => 'Changed',
          'type' => 'integer',
          'behavior' => 'changed',
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_encrypt_default_configs().
 */
function pantheon_slack_feature_encrypt_default_configs() {
  $configs = array();

  // Exported configuration: default.
  $configs['default'] = array(
    'name' => 'default',
    'label' => 'Default',
    'description' => 'The default configuration.',
    'method' => 'mcrypt_aes_cbc',
    'method_settings' => '',
    'provider' => 'key',
    'provider_settings' => array(
      'key_config' => 'pantheon_machine_token_encryptio',
    ),
    'enabled' => 1,
    'created' => 1457196843,
    'changed' => 1457200106,
  );

  return $configs;
}

/**
 * Implements hook_key_default_configs().
 */
function pantheon_slack_feature_key_default_configs() {
  $configs = array();

  // Exported key: pantheon_machine_token_encryptio.
  $configs['pantheon_machine_token_encryptio'] = array(
    'id' => 'pantheon_machine_token_encryptio',
    'label' => 'Pantheon Machine Token Encryption',
    'description' => '',
    'key_type' => 'aes_encryption',
    'key_type_settings' => array(
      'key_size' => 256,
    ),
    'key_provider' => 'file',
    'key_provider_settings' => array(
      'file_location' => '../private/pmte.key',
      'base64_encoded' => 1,
    ),
    'key_input' => 'none',
    'key_input_settings' => array(),
  );

  return $configs;
}
