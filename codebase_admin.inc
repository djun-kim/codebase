<?php
/** 
 * @file
 * Administration functions for Codebase.
 * 
 */

function codebase_admin_settings() {
  $form = array();
  $form['codebase']['codebase_target_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Directory to map'), 
    '#default_value' => variable_get('codebase_target_directory', ''),
    '#description' => t('Specify the directory which the codebase should map'),
  );
  $form['codebase']['codebase_excluded_directories'] = array(
    '#type' => 'textfield',
    '#title' => t('Subdirectories of target directory to ignore'),
    '#default_value' => variable_get('codebase_excluded_directories', ''),
    '#description' => t('Specify a comma separated list of names of directories to ignore (e.g., CVS, .svn...)'),
  );
  $form['codebase']['codebase_follow_symlinks'] = array(
    '#type' => 'select',
    '#title' => t('Follow Symbolic Links?'),
    '#options' => array('TRUE' => 'TRUE', 'FALSE' => 'FALSE'),
    '#default_value' => variable_get('codebase_follow_symlinks', ''),
    '#description' => t('Select "TRUE" if the codebase should follow symbolic links in the source directory.'),
  );
  $form['codebase']['codebase_ignored_file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Files extensions to ignore'),
    '#default_value' => variable_get('codebase_ignored_file_extensions', ''),
    '#description' => t('Enter a comma separated list of file extensions.  The codebase will ignore files with the specified extensions.'),
  );
  $form['codebase']['codebase_ignored_file_suffixes'] = array(
    '#type' => 'textfield',
    '#title' => t('Files suffixes to ignore'),
    '#default_value' => variable_get('codebase_ignored_file_suffixes', ''),
    '#description' => t('Enter a comma separated list of file suffixes (e.g., "~, %"). The codebase will ignore files with the specified suffixes.'),
  );
  $form['codebase']['codebase_ignored_file_prefixes'] = array(
    '#type' => 'textfield',
    '#title' => t('Files prefixes to ignore'),
    '#default_value' => variable_get('codebase_ignored_file_prefixes', ''),
    '#description' => t('Enter a comma separated list of file prefixes (e.g., "#, .#"). The codebase will ignore files with the specified prefixes.'),
  );
  return system_settings_form($form);
}

function codebase_initialize_admin($form_state) {
  return confirm_form(
    $form,
    t('Are you sure you want to initialize/re-initialize the codebase?'),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/content/codebase',
    t('This action destroys the existing code base internal representation. Rebuilding the new base may take time.'));
}

function codebase_initialize_admin_validate($form, &$form_state) {
  if (variable_get('codebase_target_directory', '') == '' ) {
    form_set_error('codebase_target_directory', 
                   t('Can\'t initialize codebase because the codebase directory is not set.  Please set it at the !adminlink.',
                   array('!adminlink' => l(t("codebase configuration page"),
                                           "admin/settings/codebase")
                        )
                   )
                 );
  }
}

function codebase_initialize_admin_submit($form, &$form_state) {
  $confirmed = $form_state['values']['confirm'];
  if ($confirmed) {
    codebase_initialize_code();
  }
  $form_state['redirect'] = 'admin/content/codebase';
}

function codebase_clear($form_state) {
  return confirm_form(
    $form,
    t('Are you sure you want to clear the codebase?'),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/content/codebase',
    t('This action destroys the existing code base internal representation. Rebuilding the new base may take time.'));
}

function codebase_clear_submit($form, &$form_state) {
  $confirmed = $form_state['values']['confirm'];
  if ($confirmed) {
    codebase_flush_codebase();
  }
  $form_state['redirect'] = 'admin/content/codebase';
}
