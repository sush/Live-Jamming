<?php
class RecordsController extends AppController {

	var $name = 'Records';
	var $paginate = array('order' => 'date desc');

	/*CALLBACKS*/
	function beforeFilter(){
	  parent::beforeFilter();
	  $this->AppAuth->allow('display','view');
	}
	/* /!\ CALLBACKS*/

	function index() {
		$this->Record->recursive = 0;
		$this->set('records', $this->paginate());
	}

	function display(){
	  $recordParticipant = $this->Record->find('all');
	  $this->set('recordParticipant',$recordParticipant);
	  $this->set('records', $this->paginate());
	}

	function view($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'record'));
			$this->redirect(array('action' => 'index'));
		}
		$this->set('record', $this->Record->read(null, $id));
	}

	private function __add() {
		if (!empty($this->data)) {
			$this->Record->create();
			if ($this->Record->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'record'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'record'));
			}
		}
	}

	private function __edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'record'));
			$this->redirect(array('action' => 'index'));
		}
		if (!empty($this->data)) {
			if ($this->Record->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'record'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'record'));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Record->read(null, $id);
		}
	}

	private function __delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'record'));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Record->delete($id)) {
			$this->Session->setFlash(sprintf(__('%s deleted', true), 'Record'));
			$this->redirect(array('action'=>'index'));
		}
		$this->Session->setFlash(sprintf(__('%s was not deleted', true), 'Record'));
		$this->redirect(array('action' => 'index'));
	}
}
?>