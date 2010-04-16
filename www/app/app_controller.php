<?php
class	AppController extends Controller {
  var $components = array('Session', 'Cookie','AppAuth');
    
  function beforeFilter() {
    $this->AppAuth->authorize = 'controller';
    $this->__setInfos();
    $this->__setLanguage();
  } 
  
  function beforeRender(){
  }
  
  function isAuthorized(){
    return true;
  }

  private function __setLanguage() {
    $languages = Configure::read('Config.languages');
    $languages_flipped = array_flip($languages); //Flip $languages for the proper use of in_array
    $language_cookie = $this->Cookie->read('language');
    
    /*If language is in the url and language is a known language*/
    if (isset($this->params['language']) && in_array($this->params['language'], $languages_flipped)) {
      Configure::write('Config.language', $languages[$this->params['language']]);
      $this->Cookie->write('language', $this->params['language'], null, '20 days');
    }
    /*Else If language_cookie is set language is a known language*/
    else if ($language_cookie && in_array($language_cookie, $languages_flipped)) {
      Configure::write('Config.language', $languages[$language_cookie]);
    }
    /*Else default language is set to 'fre'*/
    else
      Configure::write('Config.language', 'fre');
  }
  
  private function	__setInfos(){
    $data = $this->AppAuth->user();
    
    $this->set('userIsConnected', ((!empty($data['User']['id']))?true:false));
    $this->set('user', ((!empty($data['User']['id']))?$data['User']:''));
  }
  
  }
?>