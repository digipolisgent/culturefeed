<?php

/**
 * @file
 * Callback and handler implementations for administration pages.
 */

/**
 * Configuration form for general settings.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function culturefeed_mailing_admin_settings() {

  $form = array();
  try {

    $query = new CultureFeed_SearchMailingsQuery();
    $lists = DrupalCultureFeed_Mailing::getMailingList($query)->objects;
    $options = array('' => t('None'));

    foreach ($lists as $list) {
      $options[$list->id] = $list->name;
    }

    $form['culturefeed_mailing_list'] = array(
      '#type' => 'select',
      '#title' => t('Mailing list'),
      '#options' => $options,
      '#default_value' => variable_get('culturefeed_mailing_list', ''),
    );

    $form['culturefeed_mailing_block_description'] = array(
      '#type' => 'textfield',
      '#title' => t('Newsletter block description'),
      '#description' => t('Description displayed in the form as block'),
      '#default_value' => variable_get('culturefeed_mailing_block_description', t('Subscribe to our newsletter')),
    );

    $form['culturefeed_mailing_subscribed_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Subscribed message'),
      '#description' => t('Message after a successfull subscription'),
      '#default_value' => variable_get('culturefeed_mailing_subscribed_message', t('Successfully subscribed to our newsletter')),
    );

    $form['culturefeed_mailing_updated_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Subscription updated message'),
      '#description' => t('Message after a user has successfully updated newsletter subscription'),
      '#default_value' => variable_get('culturefeed_mailing_subscribed_message', t('Successfully subscribed to our newsletter')),
    );

    $form['culturefeed_mailing_already_subscribed_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Already subscribed message'),
      '#description' => t('Message if a user is already subscribed'),
      '#default_value' => variable_get('culturefeed_mailing_already_subscribed_message', t('You are already subscribed to our newsletter')),
    );

  }
  catch (Exception $e) {
    watchdog('culturefeed_mailing', $e->getMessage());
    drupal_set_message($e->getMessage(), WATCHDOG_ERROR);
  }
  return system_settings_form($form);
}
