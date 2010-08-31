<?php
class ArticlesController extends AppController {

	var $name = 'Articles';
	var $paginate = array('order' => array('Article.date' => 'desc'));
	var $components = array('RequestHandler');

	/*CALLBACKS*/
	function beforeFilter(){
	  parent::beforeFilter();
	  $this->AppAuth->allow('display','flux','view');
	}
	/* /!\ CALLBACKS*/

	/* FLUX RSS*/
	function flux(){
	  $articles = $this->Article->find(
					   'all',
					   array(
						 'order' => 'date desc',
						 'limit' => 10
						 )
					   );
	  $channel = array(
			   'title' => utf8_encode("Live-Jamming RSS"),
			   'description' => utf8_encode("Les dernieres news"),
			   'language' => 'fr',
			   'webMaster' => 'contact@live-jamming.com'
			   );
	  
	  $this->set(compact('articles','channel'));
	}

	/* /!\ FLUX RSS*/
	function index() {
		$this->Article->recursive = 0;
		$this->set('articles', $this->paginate());
	}

	function display() {
	  $this->set('articles', $this->paginate());
	}

	function view($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'article'));
			$this->redirect(array('action' => 'index'));
		}
		$this->set('article', $this->Article->read(null, $id));
	}

	private function __add() {
		if (!empty($this->data)) {
			$this->Article->create();
			if ($this->Article->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'article'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'article'));
			}
		}
	}

	private function __edit($id = null) {
		if (!$id && empty($this->data)) {
			$this->Session->setFlash(sprintf(__('Invalid %s', true), 'article'));
			$this->redirect(array('action' => 'index'));
		}
		if (!empty($this->data)) {
			if ($this->Article->save($this->data)) {
				$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'article'));
				$this->redirect(array('action' => 'index'));
			} else {
				$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'article'));
			}
		}
		if (empty($this->data)) {
			$this->data = $this->Article->read(null, $id);
		}
	}

	private function __delete($id = null) {
		if (!$id) {
			$this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'article'));
			$this->redirect(array('action'=>'index'));
		}
		if ($this->Article->delete($id)) {
			$this->Session->setFlash(sprintf(__('%s deleted', true), 'Article'));
			$this->redirect(array('action'=>'index'));
		}
		$this->Session->setFlash(sprintf(__('%s was not deleted', true), 'Article'));
		$this->redirect(array('action' => 'index'));
	}
}
?>