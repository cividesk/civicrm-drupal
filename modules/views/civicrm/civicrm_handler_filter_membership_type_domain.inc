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

class civicrm_handler_filter_membership_type_domain extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Membership Type Domain');
      $options = array(
        '0' => '- Current Domain -',
      );
      $domains = CRM_Core_PseudoConstant::domain();
      foreach ($domains as $id => $name) {
        $options[$id] = $name;
      }
      $this->value_options = $options;
    }
  }

  function query() {
    if (!empty($this->value)) {
      // Replace value 0 with current CiviCRM domain
      foreach ($this->value as &$domain) {
        if ($domain == '0') {
          $domain = CRM_Core_Config::domainID();
        }
      }
      parent::query();
    }
  }
}