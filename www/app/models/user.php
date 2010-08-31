<?php
class User extends AppModel {
	var $name = 'User';
	var $displayField = 'login';
	//The Associations below have been created with all possible keys, those that are not needed can be removed
	
	/* Search plugin*/
	public $actsAs = array('Search.Searchable');
	public $filterArgs = array(
				   array('name' => 'login', 'type' => 'like'),
				   array('name' => 'country_id', 'type' => 'value'),
				   array('name' => 'instrument_id', 'type' => 'value'),
				   array('name' => 'level_id', 'type' => 'value'),
				   );

	/* /!\ Search plugin*/
	var $validate = array(
			      'login' => array(
					       'alphaNumeric' => array(
								       'rule' => 'alphaNumeric',
								       'required' => true,
								       'message' => __('user_register_form_login_alphanumeric',true)),
					       'isUnique' => array(
								   'rule' => 'isUnique',
								   'message' => __('user_register_form_login_unique_message',true))
					       ),
			      'email' => array(
					       'email-1' => array(
								  'rule' => array('email'),
								  'message' => __('user_register_form_email_1_message',true)),
					       'email-2' => array(
								  'rule' => 'isUnique',
								  'message' => __('user_register_form_email_unique_message',true))
					       ),
			      'password' => array(
						  'minLength' => array(
								       'rule' => array('minLength', '8'),
								       'message' => __('user_register_form_password_message',true)),
						  ),
			      'confirm_password' => array(
							  'minLength' => array(
									       'rule' => array('minLength','8'),
									       'message' => __('user_register_form_password_message',true)),
							  'matchPassword' => array(
										   'rule' => 'matchPassword',
										   'message' => __('user_register_form_password_confirm_message',true))
							  ),
			      'captcha' => array(
						 'validateCaptcha' => array(
									    'rule' => 'validateCaptcha',
									    'message' => __('user_register_form_captcha',true))
						 )
				  );
	
	function validateCaptcha($field=null){
	  if (!defined('CAPTCHA_SESSION_ID')) {
            define('CAPTCHA_SESSION_ID', 'php_captcha');
	  }
	  if ($field['captcha'] == $_SESSION[CAPTCHA_SESSION_ID]) {
            unset ($_SESSION[CAPTCHA_SESSION_ID]);
            return true;
	  }
	  return false; 
	}

	function matchPassword($field = null){
	  return (Security::hash($field['confirm_password'], null, true) === $this->data['User']['password']);
	}

	var $belongsTo = array(
		'City' => array(
			'className' => 'City',
			'foreignKey' => 'city_id',
			'conditions' => '',
			'fields' => '',
			'order' => ''
		),
		'Country' => array(
			'className' => 'Country',
			'foreignKey' => 'country_id',
			'conditions' => '',
			'fields' => '',
			'order' => ''
		),
		'Level' => array(
			'className' => 'Level',
			'foreignKey' => 'level_id',
			'conditions' => '',
			'fields' => '',
			'order' => ''
		),
		'ConnectionType' => array(
			'className' => 'ConnectionType',
			'foreignKey' => 'connection_type_id',
			'conditions' => '',
			'fields' => '',
			'order' => ''
		),
		'Gender' => array(
			'className' => 'Gender',
			'foreignKey' => 'gender_id',
			'conditions' => '',
			'fields' => '',
			'order' => ''
				  ),
		'Instrument' => array(
			'className' => 'Instrument',
			'foreignKey' => 'instrument_id',
			'conditions' => '',
			'fields' => '',
			'order' => ''
		)
	);

	var $hasMany = array(
		'Contact' => array(
			'className' => 'Contact',
			'foreignKey' => 'user_id',
			'dependent' => false,
			'conditions' => '',
			'fields' => '',
			'order' => '',
			'limit' => '',
			'offset' => '',
			'exclusive' => '',
			'finderQuery' => '',
			'counterQuery' => ''
				   )
			     );

	var $hasAndBelongsToMany = 
	  array(
		'Record' =>
		array(
			'className' => 'Record',
			'joinTable' => 'record_participants',
			'foreignKey' => 'user_id',
			'associationForeignKey' => 'record_id',
			'conditions' => '',
			'fields' => '',
			'order' => 'date desc',
			'limit' => '',
			'offset' => '',
			'exclusive' => '',
			'finderQuery' => '',
			'counterQuery' => ''
		      )
		);
  }
?>