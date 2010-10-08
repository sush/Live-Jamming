<?php 
class AdminController extends AppController {
  
  var $name = 'Admin';
  var $helpers = Array('Html');
  var $uses = array();

  function beforeFilter(){
    parent::beforeFilter();
  }

  function display() {

    if (!isset($this->luser) || $this->luser['group_id'] != GROUP_ADMIN)
      $this->redirect('/');

    $path = func_get_args();
    
    $count = count($path);
    if (!$count) {
      $this->redirect('/');
    }
    $page = $subpage = $title = null;
    
    if (!empty($path[0])) {
      $page = $path[0];
    }
    if (!empty($path[1])) {
      $subpage = $path[1];
    }
    if (!empty($path[$count - 1])) {
      $title = Inflector::humanize($path[$count - 1]);
    }
    
    $this->set(compact('page', 'subpage', 'title'));
    $this->render(join('/', $path));
  }

  }

?>