<?php
/**
 * @file
 * Expose Taxonomy term child links to Views.
 */

/**
 * Implements hook_views_data_alter().
 */
function taxonomy_child_links_views_data_alter(&$data) {

  $data['taxonomy_term_data']['taxonomy_child_links'] = array(
    'real field' => 'tid',
    'title' => t('Child links'),
    'help' => t('A list of links to taxonomy child terms'),
    'field' => array(
      'handler' => 'views_handler_field_taxonomy_child_links',
      'no group by' => TRUE,
    ),
  );

  return $data;
}
