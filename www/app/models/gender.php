<?php
class Gender extends AppModel {
  var $name = 'Gender';
  //The Associations below have been created with all possible keys, those that are not needed can be removed
  
  var $actsAs = array('Translate' => array('wording' => 'Wordings'));
 
  var $validate = array(
			'wording' => array(
					   'rule' => '/\S+/',
					   'required' => true,
					   'allowEmpty' => false,
					   'message' => 'titre_non_vide'
					   ),
			);

  var $hasMany = array(
		       'User' => array(
				       'className' => 'User',
				       'foreignKey' => 'gender_id',
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
    }
?>