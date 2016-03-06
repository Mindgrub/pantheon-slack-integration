<?php
/**
 * @file
 * pantheon_slack_feature.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function pantheon_slack_feature_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'pantheon_slack_user-pantheon_slack_user-field_pantheon_machine_token'.
  $field_instances['pantheon_slack_user-pantheon_slack_user-field_pantheon_machine_token'] = array(
    'bundle' => 'pantheon_slack_user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'pantheon_slack_user',
    'field_name' => 'field_pantheon_machine_token',
    'label' => 'Pantheon Machine Token',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 5,
    ),
  );

  // Exported field_instance:
  // 'pantheon_slack_user-pantheon_slack_user-field_slack_team_domain'.
  $field_instances['pantheon_slack_user-pantheon_slack_user-field_slack_team_domain'] = array(
    'bundle' => 'pantheon_slack_user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'pantheon_slack_user',
    'field_name' => 'field_slack_team_domain',
    'label' => 'Slack Team Domain',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'pantheon_slack_user-pantheon_slack_user-field_slack_team_id'.
  $field_instances['pantheon_slack_user-pantheon_slack_user-field_slack_team_id'] = array(
    'bundle' => 'pantheon_slack_user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'pantheon_slack_user',
    'field_name' => 'field_slack_team_id',
    'label' => 'Slack Team ID',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'pantheon_slack_user-pantheon_slack_user-field_slack_user_id'.
  $field_instances['pantheon_slack_user-pantheon_slack_user-field_slack_user_id'] = array(
    'bundle' => 'pantheon_slack_user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'pantheon_slack_user',
    'field_name' => 'field_slack_user_id',
    'label' => 'Slack User ID',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'pantheon_slack_user-pantheon_slack_user-field_slack_user_name'.
  $field_instances['pantheon_slack_user-pantheon_slack_user-field_slack_user_name'] = array(
    'bundle' => 'pantheon_slack_user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'pantheon_slack_user',
    'field_name' => 'field_slack_user_name',
    'label' => 'Slack User Name',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Pantheon Machine Token');
  t('Slack Team Domain');
  t('Slack Team ID');
  t('Slack User ID');
  t('Slack User Name');

  return $field_instances;
}
