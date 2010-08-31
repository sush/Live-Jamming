<?php
class LevelsController extends AppController {

	var $name = 'Levels';
	
	var $paginate = array(
			      'order' => 'Level.id ASC',
			      );

	function index() {
		$this->Level->recursive = 0;
		$this->set('levels', $this->paginate());
	}

	function view($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'level'));
			$this->redirect(array('action' => 'index'));
		}
		$this->set('level', $this->Level->read(null, $id));
	}

	function add() {
		if (!empty($this->data)) {
			$this->Level->create();
			if ($this->Level->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'level'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'level'));
			}
		}
	}

	function edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'level'));
			$this->redirect(array('action' => 'index'));
		}
		if (!empty($this->data)) {
			if ($this->Level->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'level'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'level'));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Level->read(null, $id);
		}
	}

	function delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'level'));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Level->delete($id)) {
			$this->Session->setFlash(sprintf(__('%s deleted', true), 'Level'));
			$this->redirect(array('action'=>'index'));
		}
		$this->Session->setFlash(sprintf(__('%s was not deleted', true), 'Level'));
		$this->redirect(array('action' => 'index'));
	}
}
?>