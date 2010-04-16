<?php
App::import('Component', 'Auth');

class AppAuthComponent extends AuthComponent
{
  function startup(&$controller){
    $this->_set(array(
		      'userModel'      => 'User',
		      'fields'         => array('username' => 'login', 'password' => 'password'),
		      'loginAction'    => null,
		      'loginRedirect'  => '/users',
		      'logoutRedirect' => '/',
		      'autoRedirect'   => false,
		      'loginError'     => __("auth_login_error", true),
		      'authError'      => __("auth_error", true), 
		      ));
    parent::startup($controller);
  }
}
?>