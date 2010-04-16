<?php
class GendersController extends AppController {

	var $name = 'Genders';
	
	var $paginate = array(
			      'order' => 'Gender.id ASC',
			      );
	
	function index() {
	  $this->Gender->recursive = -1;
	  $this->set('genders', $this->paginate());
	}

	function view($id = null) {
	  if (!$id) {
	  	$this->Session->setFlash(sprintf(__('Invalid %s', true), 'gender'));
	  	$this->redirect(array('action' => 'index'));
	  }
		$this->set('gender', $this->Gender->read(null, $id));
	}

	function add() {
		if (!empty($this->data)) {
			$this->Gender->create();
			if ($this->Gender->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'gender'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'gender'));
			}
		}
	}

	function edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'gender'));
			$this->redirect(array('action' => 'index'));
		}
		if (!empty($this->data)) {
			if ($this->Gender->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'gender'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'gender'));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Gender->read(null, $id);
		}
	}

	function delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'gender'));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Gender->delete($id)) {
			$this->Session->setFlash(sprintf(__('%s deleted', true), 'Gender'));
			$this->redirect(array('action'=>'index'));
		}
		$this->Session->setFlash(sprintf(__('%s was not deleted', true), 'Gender'));
		$this->redirect(array('action' => 'index'));
	}
}
?>