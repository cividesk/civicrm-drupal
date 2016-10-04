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
  static $_domainName = NULL;
  static $_aclCache = NULL;

  // Prepare Chapter list
  function construct() {
    parent::construct();
    if (!self::$_domainName) {
      if (!civicrm_initialize()) {
        return;
      }
      $result = civicrm_api3('Domain', 'get', array(
        'return' => "id,name,description",
      ));

      $options = array();
      $options['0'] = 'Current Chapter';
      foreach ($result['values'] as $id => $value ) {
        $chapter = explode('-',$value['description']); // 'Arcs Foundation -' not required in drop down list
        if (!empty(trim($chapter['1']))) {
         $chapterName = trim($chapter['1']);
        } else {
          $chapterName = $chapter['0'];
        }
        $chapterName = str_replace('Chapter', '', $chapterName); // removed 'Chapter' from name
        $options[$id] = $chapterName;
      }
      self::$_domainName = $options;
    }
  }
  // called when form submitted
  function query() {
     if (!empty($this->value)) {
       $domainID = reset($this->value);
       // Current Domain have 0 value in select list
       if ($domainID == '0') {
         $domainID = CRM_Core_Config::domainID();
       }
       $acl = civicrm_handler_filter_systemdomain::getAclClause($domainID);
       if (!empty($acl)) {
         $this->query->add_where_expression(0, $acl);
       }
     }
  }

  public static function getAclClause($domainID) {
    if (! self::$_aclCache ) {
      $groupID = civicrm_api3('Setting', 'getvalue', array(
        'sequential' => 1,
        'domain_id' => $domainID,
        'name' => "domain_group_id",
      ));
      if (empty($groupID)) {
        return '';
      }
      $childOrganizations = _multisite_get_all_child_groups($groupID);
      if (!empty($childOrganizations)) {
        $groupTable = 'civicrm_group_contact';
        $groupTableAlias = 'civicrm_group_contact';
        $deletedContactClause = CRM_Core_Permission::check('access deleted contacts') ? '' : 'AND civicrm_contact.is_deleted = 0';
        $aclWhere = "(civicrm_group_contact.group_id IN (" . implode(',', $childOrganizations) . ") AND {$groupTableAlias}.status IN ('Added') $deletedContactClause)";
      }
      self::$_aclCache = $aclWhere;
    }
    return self::$_aclCache;
  }

  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Domain Name');
      $options = array();
      foreach (self::$_domainName as $id => $name) {
        $options[$id] = $name;
      }
      $this->value_options = $options;
    }
  }
}
  


