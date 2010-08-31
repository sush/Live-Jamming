<?php
class appModel extends Model {

  public function __construct($id = false, $table = null, $ds = null) {
    $this->_findMethods = array_merge($this->_findMethods, array('translated' => true));
    parent::__construct($id, $table, $ds);
  }


  function invalidate($field, $value = true) {
    return parent::invalidate($field, __d('validation_errors', $value, true));
  }

  function   _findTranslated($state, $query, $results = array()) {
    if ($state == 'before') {
      return array_merge($query, array(
                                       'fields' => array('id'),
                                       'recursive' => -1
                                       ));
    } elseif ($state == 'after') {
      if (empty($results)) {
        return $results;
      }

      $ids = Set::extract($results, "{n}.$this->name.id");
      
      switch($this->name){
      case 'Article':
	return $this->getTranslatedArticles($ids);
	break;
	
      default:
	return $this->getTranslatedLibelled($ids);
	break;
      }
    }
  }


  function getTranslatedArticles($ids){
    $translated = $this->find('all', array('conditions' => array("$this->name.id" => $ids),
				     'fields' => array('id', 'title','content'),
				     'recursive' => -1
				     ));
    $articles = $this->find('all', array('conditions' => array("$this->name.id" => $ids), 
					 'fields' => array('date'),
					 'recursive' => -1));
    $data = Set::merge($translated,$articles);
    if (empty($data)) {
      return $results;
    }

    return $data;
  }

  function getTranslatedLibelled($ids){
    $data = $this->find('all', array('conditions' => array("$this->name.id" => $ids),
				     'fields' => array('id', 'wording'),
				     'recursive' => -1
				     ));
    if (empty($data)) {
      return $results;
    }
    $data = Set::combine(
			 $data,
			 "{n}.$this->name.id",
			 "{n}.$this->name.wording"
			 );
    return $data;
  }

  }
?>