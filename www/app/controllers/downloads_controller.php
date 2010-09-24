<?php
class DownloadsController extends AppController {
  var $name = 'Downloads';
  var $uses = array();

  /*CALLBACKS*/
  function beforeFilter(){
    parent::beforeFilter();
    $this->AppAuth->allow('unix', 'windows', 'index', 'unixboost140', 'unixboost135');
  }
  /* /!\ CALLBACKS*/

  function index(){
    //if (!isset($_SESSION['Auth']['User']))
    //$this->redirect('/users/login');
  }
  
  function unixboost140(){
    
    $this->view = 'Media';
    $params = array(
		    'id' => 'livejamming.deb',
		    'name' => 'Live-Jamming',
		    'download' => true,
		    'extension' => 'deb',
		    'path' => APP . 'exe' .DS);
    $this->set($params);
  }

  function unixboost135(){
    
    $this->view = 'Media';
    $params = array(
		    'id' => 'livejamming_boost_1.35.deb',
		    'name' => 'Live-Jamming_boost_1.35',
		    'download' => true,
		    'extension' => 'deb',
		    'path' => APP . 'exe' .DS);
    $this->set($params);
  }

  function windows(){
    
    $this->view = 'Media';
    $params = array(
		    'id' => 'livejamming_setup.exe',
		    'name' => 'Live-Jamming',
		    'download' => true,
		    'extension' => 'exe',
		    'path' => APP . 'exe' .DS);
    $this->set($params);
  }
  
  }


?>