<?php
class InstrumentsController extends AppController {

	var $name = 'Instruments';

	var $paginate = array(
			      'order' => 'Level.id ASC'
			      );

	function index() {
		$this->Instrument->recursive = 0;
		$this->set('instruments', $this->paginate());
	}

	function view($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'instrument'));
			$this->redirect(array('action' => 'index'));
		}
		$this->set('instrument', $this->Instrument->read(null, $id));
	}

	function add() {
		if (!empty($this->data)) {
			$this->Instrument->create();
			if ($this->Instrument->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'instrument'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'instrument'));
			}
		}
	}

	function edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'instrument'));
			$this->redirect(array('action' => 'index'));
		}
		if (!empty($this->data)) {
			if ($this->Instrument->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'instrument'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'instrument'));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Instrument->read(null, $id);
		}
	}

	function delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'instrument'));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Instrument->delete($id)) {
			$this->Session->setFlash(sprintf(__('%s deleted', true), 'Instrument'));
			$this->redirect(array('action'=>'index'));
		}
		$this->Session->setFlash(sprintf(__('%s was not deleted', true), 'Instrument'));
		$this->redirect(array('action' => 'index'));
	}
}
?>