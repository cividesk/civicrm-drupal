<?php
/*
 +--------------------------------------------------------------------+
 | CiviCRM version 4.6                                                |
 +--------------------------------------------------------------------+
 | This file is a part of CiviCRM.                                    |
 |                                                                    |
 | CiviCRM is free software; you can copy, modify, and distribute it  |
 | under the terms of the GNU Affero General Public License           |
 | Version 3, 19 November 2007 and the CiviCRM Licensing Exception.   |
 |                                                                    |
 | CiviCRM is distributed in the hope that it will be useful, but     |
 | WITHOUT ANY WARRANTY; without even the implied warranty of         |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.               |
 | See the GNU Affero General Public License for more details.        |
 |                                                                    |
 | You should have received a copy of the GNU Affero General Public   |
 | License and the CiviCRM Licensing Exception along                  |
 | with this program; if not, contact CiviCRM LLC                     |
 | at info[AT]civicrm[DOT]org. If you have questions about the        |
 | GNU Affero General Public License or the licensing of CiviCRM,     |
 | see the CiviCRM license FAQ at http://civicrm.org/licensing        |
 +--------------------------------------------------------------------+
*/

/**
 * Field hanlder to allow filtering by CiviCRM domain.
 */
class civicrm_handler_filter_systemdomain extends views_handler_filter_in_operator {
  static $_domainList = array();

  function construct() {
    parent::construct();
    if (!civicrm_initialize()) {
      return;
    }
    if (!self::$_domainList) {
      $options = array();
      $options['0'] = 'Current Chapter';

      $result = civicrm_api3('Domain', 'get', array(
        'return' => "id,name,description",
      ));

      foreach ($result['values'] as $id => $value ) {
        $chapter = explode('-',$value['description']);
        if (!empty(trim($chapter['1']))) {
          $chapterName = trim($chapter['1']);
        } else {
          $chapterName = $chapter['0'];
        }
        $chapterName = str_replace('Chapter', '', $chapterName);
        $options[$id] = $chapterName;//$value['description'];
      }
      self::$_domainList = $options;
    }
  }

  function query() {
    if (!empty($this->value)) {
      $domainID = reset($this->value);
      // Current Domain have 0 value in select list
      if ($domainID == '0') {
        $domainID = CRM_Core_Config::domainID();
      }
      $aclClause = self::getAclClause($domainID);
      if (!empty($aclClause)) {
        $this->ensure_my_table();
        $this->query->add_where_expression(0, $aclClause);
      }
    }
  }

  public static function getAclClause($domainID) {
    $aclClause = '';
    $groupID = civicrm_api3('Setting', 'getvalue', array(
      'sequential' => 1,
      'domain_id' => $domainID,
      'name' => "domain_group_id",
    ));
    if (!empty($groupID)) {
      // Lines below adapted from multisite_civicrm_aclWhereClause() in org.civicrm.multisite
      $childOrganizations = _multisite_get_all_child_groups($groupID);
      if (!empty($childOrganizations)) {
        $groupTable = 'civicrm_group_contact';
        $aclClause = "{$groupTable}.group_id IN (" . implode(',', $childOrganizations) . ") AND {$groupTable}.status IN ('Added')";
      }
    }
    return $aclClause;
  }

  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Domain Name');
      $options = array();
      foreach (self::$_domainList as $id => $name) {
        $options[$id] = $name;
      }
      $this->value_options = $options;
    }
  }
}