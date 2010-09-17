<?php
class UsersController extends AppController {

  var $name = 'Users';
  var $components = array('Captcha','Search.Prg');
  var $paginate = array('limit' => 5, 'order' => array('User.created' => 'desc'));

  /*CALLBACKS*/
  function beforeFilter(){
    parent::beforeFilter();
    $this->AppAuth->allow('register', 'captcha_image','find','profil', 'getLastMembers');
  }
  /* /!\ CALLBACKS*/
  
  /*CAPTCHA*/
  function captcha_image()
  {
    $this->Captcha->image();
  } 
  /* /!\ CAPTCHA*/

  /* SEARCH PLUGIN*/
  public $presetVars = array(
			     array('field' => 'login', 'type' => 'value'),
			     array('field' => 'country_id', 'type' => 'value'),
			     array('field' => 'instrument_id', 'type' => 'value'),
			     array('field' => 'level_id', 'type' => 'value')
			     );

  public function find(){
    $this->Prg->commonProcess();
    $this->paginate['conditions'] = $this->User->parseCriteria($this->passedArgs);
    $this->set('members', $this->paginate());
    $this->set('instruments',$this->User->Instrument->find('translated'));
    $this->set('levels',$this->User->Level->find('translated'));
    $this->__loadHtmlSelects();
  }
  /* /!\ SEARCH PLUGIN*/

  public function profil(){
    Controller::loadModel('Record');
    if (!$recordParticipant = Cache::read('recParticipant','records')) {
      $recordParticipant = $this->Record->find('all');
      Cache::write('recParticipant',$recordParticipant,'records');
    }
    $user = $this->User->find('first', array('conditions' => array('login' => $this->params['pass']), 'recursive' => 1));
    if (!empty($user)) {
      $this->set('member',$user);
      $this->set('recordParticipant',$recordParticipant);
      $this->set('instruments',$this->User->Instrument->find('translated'));
      $this->set('levels',$this->User->Level->find('translated'));
    } 
  }

  /*CONNEXION*/
  function login() {
    if (!empty($this->data)) {
      $this->data['User']['login'] = $this->data['User']['connexion_login'];
      $this->data['User']['password'] = Security::hash($this->data['User']['connexion_password'], null, true);
      if($this->AppAuth->login($this->data)) {
	if(isset($_SESSION['Forum']))
	  $this->redirect($this->AppAuth->loginRedirect = array('plugin' => 'forum', 'controller' => 'home', 'action' => 'index'));
	else
	  $this->redirect($this->AppAuth->loginRedirect = array('controller' => 'pages', 'action' => 'display', 'home'));
      }
      $this->redirect(array('controller' => 'users', 'action' => 'login'));
    }
  }
  
  function logout(){
    $this->Session->destroy();
    $this->redirect($this->AppAuth->logout());
  }
  /* /!\ CONNEXION*/
  
  function index() {
    $this->User->recursive = 0;
    $this->set('users', $this->paginate());
  }
  
  function register(){
    $this->__add();
  }

  function changepassword(){
    if (!empty($this->data)){
      $user = $this->User->read(null, $this->AppAuth->user('id'));
      if (Security::hash($this->data['User']['old_password'], null, true) != $user['User']['password'])
	$this->User->invalidate('old_password','Old password is not valid');
      else {
	if ($this->data['User']['new_password'] != $this->data['User']['confirm_password'])
	  $this->User->invalidate('confirm_password','Confirm password doesn\'t match');
	else{
	  $this->data['User']['password'] = Security::hash($this->data['User']['confirm_password'], null, true);
	  if ($this->User->save($this->data, array('fieldlist' => array('password')))){
	    $this->Session->setFlash(sprintf(__('Password updated, please login again.', true), 'user'));
	    $this->redirect(array('controller' => 'pages', 'action' => 'display', 'home'));
	  }
	  else
	    $this->render();
	}
      }
    }
  }

  function account(){
    $validateAccount = $this->User->validate;
    if (!empty($this->data) && empty($this->data['User']['password'])){
      unset($validateAccount['password']);
      unset($validateAccount['confirm_password']);
    }
    
    unset($validateAccount['captcha']);
    unset($validateAccount['login']);

    $this->User->validate = $validateAccount;
    $this->__edit($this->AppAuth->user('id'));
    
    $this->__loadHtmlSelects();
  }

  function records() {
    Controller::loadModel('Record');
    $recordParticipant = $this->Record->find('all');
    $this->set('records',$recordParticipant);
  }
  
  private function __view($id = null) {
    if (!$id) {
      $this->Session->setFlash(sprintf(__('Invalid %s', true), 'user'));
      $this->redirect(array('action' => 'index'));
    }
    $this->set('user', $this->User->read(null, $id));
  }
  
  private function __add() {
    if (!empty($this->data)) {
      $this->User->create();
      if ($this->User->save($this->data)) {
	$this->AppAuth->login($this->data);
	$this->redirect($this->AppAuth->loginRedirect = array('controller' => 'pages', 'action' => 'display', 'home'));
      } else {
	$this->data['User']['password'] = '';
	$this->data['User']['confirm_password'] = '';
	$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'user'));
      }
    }	
    $this->__loadHtmlSelects();
  }

  private function __edit($id = null) {
    if (!$id && empty($this->data)) {
      $this->Session->setFlash(sprintf(__('Invalid %s', true), 'user'));
      $this->redirect(array('action' => 'index'));
    }
    if (!empty($this->data)){
      if ($this->User->save($this->data)) {
	$this->Session->setFlash(sprintf(__('The %s has been saved', true), 'user'));
	$this->redirect(array('action' => 'account'));
      } else {
	$this->Session->setFlash(sprintf(__('The %s could not be saved. Please, try again.', true), 'user'));
	$this->data['User']['password'] = '';
	$this->data['User']['confirm_password'] = '';
      }
    }
    if (empty($this->data)) {
      $this->data = $this->User->read(null, $id);
      $this->data['User']['password'] = '';
    }
  }

  private function __delete($id = null) {
    if (!$id) {
      $this->Session->setFlash(sprintf(__('Invalid id for %s', true), 'user'));
      $this->redirect(array('action'=>'index'));
    }
    if ($this->User->delete($id)) {
      $this->Session->setFlash(sprintf(__('%s deleted', true), 'User'));
      $this->redirect(array('action'=>'index'));
    }
    $this->Session->setFlash(sprintf(__('%s was not deleted', true), 'User'));
    $this->redirect(array('action' => 'index'));
  }

  private function __loadHtmlSelects(){
    $genders = $this->User->Gender->find('translated');
    $levels = $this->User->Level->find('translated');
    $countries = $this->User->Country->find('list', array('fields' => 'country'));
    $connectionTypes = $this->User->ConnectionType->find('translated');
    $instruments = $this->User->Instrument->find('translated');
    $this->set(compact('genders','levels','connectionTypes','countries','instruments'));
  }

  function getLastMembers() {
    return($this->User->find('all',array('fields' => array('id','login','created','instrument_id'),'order' => 'created DESC', 'limit' => 5)));
  }

  }
?>