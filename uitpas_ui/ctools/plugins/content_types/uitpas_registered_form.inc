<?php

/**
 * @file
 * Plugin to provide a content type for uitpas registered form.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Uitpas: registered form'),
  'description' => t('Uitpas: registered form.'),
  'category' => t('Uitpas'),
  'required context' => new ctools_context_required(t('Uitpas user'), 'uitpas_user'),
);

function uitpas_ui_uitpas_registered_form_content_type_edit_form($form, &$form_state) {
  return $form;
}

function uitpas_ui_uitpas_registered_form_content_type_render($subtype, $conf, $args, $context) {
  if ($context->data) {
    $uitpas_user = $context->data->user;
    $cf = $context->data->cf;
    $block = new stdClass();
    $block->title = t('You are now registered on UITPAS');
    $form_id = 'uitpas_ui_uitpas_registered_form_content_type_render_form';
    $block->content = drupal_get_form($form_id, $uitpas_user, $cf);
    return $block;
  }
}

function uitpas_ui_uitpas_registered_form_content_type_render_form($form, &$form_state, $uitpas_user, $cf) {
  $form['uitpas_user'] = array(
    '#type' => 'value',
    '#value' => $uitpas_user,
  );
  $form['cf'] = array(
    '#type' => 'value',
    '#value' => $cf,
  );
  $form['publish_actions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make my UITPAS actions available for others'),
  );
  $form['newsletter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Register for the monthly UITPAS newsletter'),
  );
  $form['actions'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Confirm'),
    ),
  );
  $form['#suffix'] = l(t('Click here to continue to the homepage'), '<front>');
  return $form;
}

function uitpas_ui_uitpas_registered_form_content_type_render_form_submit(&$form, &$form_state) {
  //preferences
  try {
    $uitpas_user = $form_state['values']['uitpas_user'];
    $cf = $form_state['values']['cf'];
    $preferences = new CultureFeed_Preferences();
    $private = ($form_state['values']['publish_actions']) ? FALSE : TRUE;
    $preference = new CultureFeed_ActivityPrivacyPreference(CultureFeed_Activity::TYPE_UITPAS, $private);
    $preferences->activityPrivacyPreferences[] = $preference;
    $cf->setUserPreferences($uitpas_user->id, $preferences);
    drupal_set_message(t('Your changes have been saved.'));
    $form_state['redirect'] = '<front>';
  }
  catch (Exception $e) {
    watchdog_exception('uitpas_ui_content_type_registered_form', $e);
    drupal_set_message(t('An error occured.'), 'error');
  }
}