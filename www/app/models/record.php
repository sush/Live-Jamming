<?php
class Record extends AppModel {
	var $name = 'Record';
	//The Associations below have been created with all possible keys, those that are not needed can be removed

	var $hasMany = array(
		'RecordParticipant' => array(
			'className' => 'RecordParticipant',
			'foreignKey' => 'record_id',
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
		'User' =>
		array(
		      'className' => 'User',
		      'joinTable' => 'record_participants',
		      'foreignKey' => 'record_id',
		      'associationForeignKey' => 'user_id',
		      'conditions' => '',
		      'fields' => 'login',
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