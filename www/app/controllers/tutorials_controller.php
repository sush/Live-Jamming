<?php
class TutorialsController extends AppController {
  var $name = 'Tutorials';
  var $uses = array();
  

  /*CALLBACKS*/
  function beforeFilter() {
    parent::beforeFilter();
    $this->AppAuth->allow('index');
  }
  /* /!\ CALLBACKS*/
  
  function index() {
    
  }
  
  }

?>