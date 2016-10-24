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
 * Build the $data array for CiviMember related tables
 * Includes the following tables
 * civicrm_membership
 * civicrm_membership_type
 */
function _civicrm_member_data(&$data, $enabled) {
  //----------------------------------------------------------------
  // CIVICRM Memberships are here with all the connections.
  //----------------------------------------------------------------


  $data['civicrm_membership']['table']['group'] = t('CiviCRM Memberships');

  $data['civicrm_membership']['table']['base'] = array(
    // Governs the whole mozilla
    'field' => 'id',
    'title' => t('CiviCRM Memberships'),
    'help' => t("View displays CiviCRM Memberships, with connection to contacts."),
  );
  $data['civicrm_membership']['table']['join'] = array(
    // Directly links to contact table - link A
    'civicrm_contact' => array(
      'left_field' => 'id',
      'field' => 'contact_id',
    ),
    // Directly links to membership_type table
    'civicrm_membership_type' => array(
      'left_field' => 'id',
      'field' => 'membership_type_id',
    ),
  );

  //Display Memberships in User Views
  $data['civicrm_membership']['table']['join']['users'] = array(
    'left_table' => 'civicrm_uf_match',
    'left_field' => 'contact_id',
    'field' => 'contact_id',
  );

  $data['civicrm_membership_type']['table']['group'] = t('CiviCRM Membership Types');

  $data['civicrm_membership_type']['table']['base'] = array(
    // Governs the whole mozilla
    'field' => 'id',
    'title' => t('CiviCRM Membership Types'),
    'help' => t("View displays CiviCRM Membership Types."),
  );
  $data['civicrm_membership_type']['table']['join'] = array(
    // Directly links to membership table
    'civicrm_membership' => array(
      'left_field' => 'membership_type_id',
      'field' => 'id',
    ),
  );

  //CiviCRM Memberships - FIELDS

  //Numeric Membership ID
  $data['civicrm_membership']['id'] = array(
    'title' => t('Membership ID'),
    'help' => t('The numeric ID of the Membership'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //Membership Type
  $data['civicrm_membership']['membership_type'] = array(
    'title' => t('Membership Type'),
    'real field' => 'membership_type_id',
    'help' => t('The Type of Membership'),
    'field' => array(
      'handler' => 'civicrm_handler_field_pseudo_constant',
      'click sortable' => TRUE,
      'pseudo class' => 'CRM_Member_PseudoConstant',
      'pseudo method' => 'membershipType',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
    'filter' => array(
      'handler' => 'civicrm_handler_filter_pseudo_constant',
      'allow empty' => TRUE,
      'pseudo class' => 'CRM_Member_PseudoConstant',
      'pseudo method' => 'membershipType',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //Membership Join date
  $data['civicrm_membership']['join_date'] = array(
    'title' => t('Join Date'),
    'help' => t('The Membership\'s Start Date'),
    'field' => array(
      'handler' => 'civicrm_handler_field_datetime',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'civicrm_handler_filter_datetime',
      'is date' => TRUE,
    ),
    'sort' => array(
      'handler' => 'civicrm_handler_sort_date',
    ),
  );

  civicrm_views_add_date_arguments($data['civicrm_membership'], array(
    'title' => 'Join Date',
      'name' => 'join_date',
    ));

  //Membership start date
  $data['civicrm_membership']['start_date'] = array(
    'title' => t('Start Date'),
    'help' => t('The Membership\'s Start Date'),
    'field' => array(
      'handler' => 'civicrm_handler_field_datetime',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'civicrm_handler_filter_datetime',
      'is date' => TRUE,
    ),
    'sort' => array(
      'handler' => 'civicrm_handler_sort_date',
    ),
  );

  civicrm_views_add_date_arguments($data['civicrm_membership'], array(
    'title' => 'Start Date',
      'name' => 'start_date',
    ));


  //Membership end date
  $data['civicrm_membership']['end_date'] = array(
    'title' => t('End Date'),
    'help' => t('The Membership\'s End Date'),
    'field' => array(
      'handler' => 'civicrm_handler_field_datetime',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'civicrm_handler_filter_datetime',
      'is date' => TRUE,
    ),
    'sort' => array(
      'handler' => 'civicrm_handler_sort_date',
    ),
  );

  civicrm_views_add_date_arguments($data['civicrm_membership'], array(
    'title' => 'End Date',
      'name' => 'end_date',
    ));


  //Membership Source
  $data['civicrm_membership']['source'] = array(
    'title' => t('Source'),
    'help' => t('Source of the relationship'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  //Membership Status
  $data['civicrm_membership']['status'] = array(
    'title' => t('Status'),
    'real field' => 'status_id',
    'help' => t('The Status of the Membership'),
    'field' => array(
      'handler' => 'civicrm_handler_field_pseudo_constant',
      'click sortable' => TRUE,
      'pseudo class' => 'CRM_Member_PseudoConstant',
      'pseudo method' => 'membershipStatus',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
    'filter' => array(
      'handler' => 'civicrm_handler_filter_pseudo_constant',
      'allow empty' => TRUE,
      'pseudo class' => 'CRM_Member_PseudoConstant',
      'pseudo method' => 'membershipStatus',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //BOOLEAN : IS Status Overridden
  $data['civicrm_membership']['is_override'] = array(
    'title' => t('Status overridden?'),
    'help' => t('Is the membership status overridden?'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  //Membership end date
  $data['civicrm_membership']['reminder_date'] = array(
    'title' => t('Reminder Date'),
    'help' => t('The Membership\'s Reminder Date'),
    'field' => array(
      'handler' => 'civicrm_handler_field_datetime',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'civicrm_handler_filter_datetime',
      'is date' => TRUE,
    ),
    'sort' => array(
      'handler' => 'civicrm_handler_sort_date',
    ),
  );

  civicrm_views_add_date_arguments($data['civicrm_membership'], array(
    'title' => 'Reminder Date',
      'name' => 'reminder_date',
    ));

  //Numeric Membership Owner ID
  $data['civicrm_membership']['owner_membership_id'] = array(
    'title' => t('Membership Owner ID'),
    'help' => t('The numeric ID Contact that owns the membership'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //BOOLEAN : IS test membership
  $data['civicrm_membership']['is_test'] = array(
    'title' => t('Test Membership?'),
    'help' => t('Is this a test membership?'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  //BOOLEAN : IS Pay later
  $data['civicrm_membership']['is_pay_later'] = array(
    'title' => t('Is Pay Later'),
    'help' => t('Is the Membership pay later?'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Link to Campaign Table
  if (isset($enabled['CiviCampaign'])) {
    $data['civicrm_membership']['campaign_id'] = array(
      'title' => t('Campaign'),
      'help' => t('Membership -> Campaign'),
      'relationship' => array(
        'base' => 'civicrm_campaign',
        'base field' => 'id',
        'handler' => 'views_handler_relationship',
        'label' => t('Membership -> Campaign'),
      ),
    );
  }

  //CiviCRM Membership Type - FIELDS

  //Numeric Membership Type ID
  $data['civicrm_membership_type']['id'] = array(
    'title' => t('Membership Type ID'),
    'help' => t('The numeric ID of the Membership Type'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //Membership Type
  $data['civicrm_membership_type']['name'] = array(
    'title' => t('Membership Type Name'),
    'help' => t('The Membership Type Name'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //Membership Type Domain
  $data['civicrm_membership_type']['domain'] = array(
    'title' => t('Membership Type Domain'),
    'real field' => 'domain_id',
    'help' => t('Membership Type Domain'),
    'field' => array(
      'handler' => 'civicrm_handler_field_pseudo_constant',
      'click sortable' => TRUE,
      'pseudo class' => 'CRM_Core_PseudoConstant',
      'pseudo method' => 'domain',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument',
    ),
    'filter' => array(
      'handler' => 'civicrm_handler_filter_membership_type_domain',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //Membership Type Description
  $data['civicrm_membership_type']['description'] = array(
    'title' => t('Membership Type Description'),
    'help' => t('The Membership Type Description'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

}
