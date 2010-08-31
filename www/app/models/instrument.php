<?php
class Instrument extends AppModel {
	var $name = 'Instrument';
	//The Associations below have been created with all possible keys, those that are not needed can be removed

	var $actsAs = array('Translate' => array('wording'=>'Wording'));

	var $validate = array(
			      'wording' => array(
						 'rule' => '/\S+/',
						 'required' => true,
						 'allowEmpty' => false,
						 'message' => 'titre_non_vide'
						 )
			      );


	var $hasMany = array(
		'User' => array(
			'className' => 'User',
			'foreignKey' => 'instrument_id',
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