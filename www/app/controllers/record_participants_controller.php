<?php
class RecordParticipantsController extends AppController {

	var $name = 'RecordParticipants';

	function index() {
		$this->RecordParticipant->recursive = 0;
		$this->set('recordParticipants', $this->paginate());
	}

	function view($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'record participant'));
			$this->redirect(array('action' => 'index'));
		}
		$this->set('recordParticipant', $this->RecordParticipant->read(null, $id));
	}

	function add() {
		if (!empty($this->data)) {
			$this->RecordParticipant->create();
			if ($this->RecordParticipant->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'record participant'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'record participant'));
			}
		}
		$records = $this->RecordParticipant->Record->find('list');
		$users = $this->RecordParticipant->User->find('list');
		$this->set(compact('records', 'users'));
	}

	function edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'record participant'));
			$this->redirect(array('action' => 'index'));
		}
		if (!empty($this->data)) {
			if ($this->RecordParticipant->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'record participant'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'record participant'));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->RecordParticipant->read(null, $id);
		}
		$records = $this->RecordParticipant->Record->find('list');
		$users = $this->RecordParticipant->User->find('list');
		$this->set(compact('records', 'users'));
	}

	function delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'record participant'));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->RecordParticipant->delete($id)) {
			$this->Session->setFlash(sprintf(__('%s deleted', true), 'Record participant'));
			$this->redirect(array('action'=>'index'));
		}
		$this->Session->setFlash(sprintf(__('%s was not deleted', true), 'Record participant'));
		$this->redirect(array('action' => 'index'));
	}
}
?>