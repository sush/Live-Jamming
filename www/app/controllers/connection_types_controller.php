<?php
class ConnectionTypesController extends AppController {

  var $name = 'ConnectionTypes';
  
  var $paginate = array(
			'order' => 'connection_types.id ASC');

	function index() {
		$this->ConnectionType->recursive = 0;
		$this->set('connectionTypes', $this->paginate());
	}

	function view($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'connection type'));
			$this->redirect(array('action' => 'index'));
		}
		$this->set('connectionType', $this->ConnectionType->read(null, $id));
	}

	function add() {
		if (!empty($this->data)) {
			$this->ConnectionType->create();
			if ($this->ConnectionType->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'connection type'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'connection type'));
			}
		}
	}

	function edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'connection type'));
			$this->redirect(array('action' => 'index'));
		}
		if (!empty($this->data)) {
			if ($this->ConnectionType->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'connection type'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'connection type'));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->ConnectionType->read(null, $id);
		}
	}

	function delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'connection type'));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->ConnectionType->delete($id)) {
			$this->Session->setFlash(sprintf(__('%s deleted', true), 'Connection type'));
			$this->redirect(array('action'=>'index'));
		}
		$this->Session->setFlash(sprintf(__('%s was not deleted', true), 'Connection type'));
		$this->redirect(array('action' => 'index'));
	}
}
?>