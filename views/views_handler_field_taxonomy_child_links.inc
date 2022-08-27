<?php
/**
 * @file
 * Views handler: List of links to taxonomy child terms
 */

/**
 * Returns a formatted list of links to taxonomy child terms.
 */
class views_handler_field_taxonomy_child_links extends views_handler_field {

  /**
   * Overrides views_handler::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['link_path'] = array(
      'default' => 'taxonomy/[tid]',
    );
    $options['delimiter'] = array(
      'default' => ', ',
    );
    $options['max_children'] = array(
      'default' => 5,
    );

    return $options;
  }

  /**
   * Overrides views_handler::options_form().
   */
  function options_form(&$form, &$form_state) {
    $options = $this->options;

    $form['link_path'] = array(
      '#title' => t('Link path'),
      '#description' => t('Enter the link path to use for the taxonomy link. Use [tid] for the term ID of the child term.'),
      '#type' => 'textfield',
      '#default_value' => $options['link_path'],
    );

    $form['delimiter'] =  array(
      '#title' => t('Delimiter'),
      '#description' => t('Enter the delimiter to be used for imploding the list of children.'),
      '#type' => 'textfield',
      '#size' => 4,
      '#default_value' => $options['delimiter'],
    );

    $form['max_children'] = array(
      '#title' => t('Maximum children'),
      '#description' => t('Enter the maximum number of child terms to list. If there are more child terms than this, ellipsis will be used. Enter 0 for no limit.'),
      '#type' => 'textfield',
      '#size' => 4,
      '#default_value' => $options['max_children'],
      '#element_validate' => array('element_validate_integer'),
    );

    parent::options_form($form, $form_state);

    // Rewrite the markup for a parent form item.
    $form['form_description']['#markup'] = t('A list of taxonomy child terms. Style and rewrite settings you provide below will be applied individually to each of the child terms.');
  }

  /**
   * Overrides views_handler_field::pre_render()
   */
  function pre_render(&$values) {
    foreach ($values as $value) {
      $value->taxonomy_children = taxonomy_term_load_children($value->tid);
    }
  }

  /**
   * Overrides views_handler_field::render()
   */
  function render($values) {
    $options = $this->options;
    $links = array();
    $max = $this->options['max_children'];
    $count = 0;
    foreach ($values->taxonomy_children as $child) {
      if ($max && $count >= $max) {
        $links[] = '&hellip;';
        break;
      }
      $link_path = str_replace('[tid]', $child->tid, $options['link_path']);
      $links[] = l($child->name, $link_path);
      $count++;
    }
    return implode($options['delimiter'], $links);
  }
}
