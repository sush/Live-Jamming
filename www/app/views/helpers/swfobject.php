<?php
  /**
   * Insertion d'une animation Flash avec SWFObject
   * http://code.google.com/p/swfobject/
   */
class SwfobjectHelper extends Helper
{
  /**
   * Swfobject Flash vars.
   *
   * @var array
   */
  var $__flashvars = array();
  /**
   * Swfobject params.
   *
   * @var array
   */
  var $__swfparams = array();
  /**
   * Swfobject Attributes.
   * 
   * @var array
   */
  var $__attributes = array();
 
  /**
   * Options par défaut
   *
   * @var array
   */
  var $__baseOptions = array(
			     'width'   => '640',
			     'height'  => '480',
			     'version' => '9.0.0',
			     'express' => 'expressInstall.swf'
			     );  
 
  /**
   * Création de l'objet Flash
   *
   * @param string $path Chemin vers l'animation Flash
   * @param string $id Id de l'élément HTML qui sera remplacé par l'animation
   * @param array $options
   * @return Code HTML à insérer entre <head>...</head>
   */
  function create($path, $id = 'flashcontent', $options = array())
  {
    $options = am($this->__baseOptions, $options);
 
    $out = '<script type="text/javascript">';
    $out .= "\n";
 
    // Flashvars
    $out .= $this->javascriptObject('flashvars', $this->__flashvars);
 
    // Params
    $out .= $this->javascriptObject('params', $this->__swfparams);
 
    // Attributes
    $out .= $this->javascriptObject('attributes', $this->__attributes);
 
    // SWF Object
    $out .= 'swfobject.embedSWF("';
    $out .= str_replace('//', '/', $this->webroot.$path);
    $out .= '", "';
    $out .= $id;
    $out .= '", "';
    $out .= join('", "', $options);
    $out .= '", flashvars, params, attributes';
    $out .= ');';
    $out .= "\n";
    $out .='</script>';
 
    return $out;
  }
 
  /**
   * Ajout d'une Flashvar
   *
   * @param string $var
   * @param mixed $value
   */
  function addFlashvar($var, $value = null)
  {
    if(is_array($var))
      {
	$this->__flashvars = am($var, $this->__flashvars);  
      }
    else if($value !== null)
      {
	$this->__flashvars[$var] = $value;
      }
  }
 
  /**
   * Ajout d'un Param
   *
   * @param string $var
   * @param mixed $value
   */
  function addParam($var, $value)
  {
    if(is_array($var))
      {
	$this->__swfparams = am($var, $this->__swfparams);  
      }
    else if($value !== null)
      {
	$this->__swfparams[$var] = $value;
      }
  }
 
  /**
   * Ajout d'un Attribut
   *
   * @param string $var
   * @param mixed $value
   */
  function addAttribute($var, $value)
  {
    if(is_array($var))
      {
	$this->__attributes = am($var, $this->__attributes);
      }
    else if($value !== null)
      {
	$this->__attributes[$var] = $value;
      }
  }
 
  /**
   * Renvoie une liste de valeurs sous forme d'un objet Javascript
   *
   * @param string $name Nom de l'objet
   * @param mixed $values
   */
  function javascriptObject($name, $values = array())
  {
    $params = array();
 
    foreach ($values as $key => $value)
      {
	$params[] = $key . ': "' . $value . '"';
      }
 
    return 'var ' . $name . ' = {' . join(",\n", $params) . "};\n";
  }
}
?>