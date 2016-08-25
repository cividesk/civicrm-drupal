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
class civicrm_handler_filter_groupdomain extends views_handler_filter_numeric {
  static $_aclCache = NULL;
  /**
   * Add an additonal operator which takes no arguments to the existing list provided by views_handler_filter_numeric.
   */
  function operators() {
    //$operators = parent::operators();
    $operators['current_domain'] = array(
      'title' => t('Current CiviCRM domain'),
      'method' => 'current_domain',
      'short' => t('current domain'),
      'values' => 0,
    );
    return $operators;
  }

  /**
   * Grab the current domain id using the civicrm api and filter the query.
   */
  function current_domain($field) {
    if (!civicrm_initialize()) {
      return FALSE;
    }
    $acl = civicrm_handler_filter_groupdomain::getAclClause();
    $this->query->add_where_expression(0, $acl['aclWhereClause']);
  }
  public static function getAclClause() {
    if (! self::$_aclCache ) { 
      $acl=  new CRM_Contact_BAO_Query();
      $acl->generatePermissionClause(false, true);
      //$aclFrom  = CRM_Utils_Array::value('civicrm_group_contact', $acl->_whereTables);
      $aclFrom  = CRM_Utils_Array::value('multisiteGroupTable', $acl->_whereTables);
      $aclWhere = $acl->_permissionWhereClause ;
      $aclWhere = str_replace('multisiteGroupTable', 'civicrm_group_contact', $aclWhere);
      $aclWhere = str_replace('contact_a', 'civicrm_contact', $aclWhere);
      self::$_aclCache = array('aclFromClause' => $aclFrom, 'aclWhereClause' => $aclWhere);
    }
    return self::$_aclCache;
  }
}
