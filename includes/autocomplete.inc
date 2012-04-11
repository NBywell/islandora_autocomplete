<?php

/**
 * @file
 *
 * Callback for querying a autocomplete url.
 */

/**
 * The primary callback that returns the requested autocomplete values.
 *
 * @param string $name
 *   The unique name of the autocomplete url to use.
 *
 * @param string $query
 *   The search query for the autocomplete.
 */
function islandora_autocomplete_query($name, $query) {
  module_load_include('inc', 'islandora_autocomplete', 'islandora_autocomplete.db');
  $url = islandora_autocomplete_db_get_url_by_name($name);
  $results = $url ? islandora_autocomplete_query_source($url->id, $url->source, $query) : array();
  return drupal_json($results);
}

/**
 * Query the source.
 * 
 * @param int $id
 *   The unique id for the requested Autocomplete URL.
 * @param string $source
 *   The source used to populate the autocomplete URL.
 * @param string $query
 *   The search query for the autocomplete.
 * 
 * @return array
 *   The results of the query
 */
function islandora_autocomplete_query_source($id, $source, $query) {
  $query_hook = "islandora_autocomplete_url_query_{$source}";
  $results = function_exists($query_hook) ? call_user_func($query_hook, $id, $query) : array();
  asort($results); // Sort alphabetically.
  return $results;
}