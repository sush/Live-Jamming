<?php
/**
 *
 * PHP versions 4 and 5
 *
 * CakePHP(tm) : Rapid Development Framework (http://cakephp.org)
 * Copyright 2005-2010, Cake Software Foundation, Inc. (http://cakefoundation.org)
 *
 * Licensed under The MIT License
 * Redistributions of files must retain the above copyright notice.
 *
 * @copyright     Copyright 2005-2010, Cake Software Foundation, Inc. (http://cakefoundation.org)
 * @link          http://cakephp.org CakePHP(tm) Project
 * @package       cake
 * @subpackage    cake.cake.libs.view.templates.errors
 * @since         CakePHP(tm) v 0.10.0.1076
 * @license       MIT License (http://www.opensource.org/licenses/mit-license.php)
 */
?>
<div class="wrapper col2">
  <div id="breadcrumb">
    
  </div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col3">
  <div id="container">
    
    <div style="width:40%;float:left;">
      <img src="/img/404.jpg"/>
    </div>
    <div style="width:55%;float:left;">
      <p style="font-size: 2em;">
      <strong> 404 <?php echo $name; ?></strong>
      <p style="font-size:1.2em;"><?php printf(__('The requested address %s was not found on this server.', true), "<strong>'{$message}'</strong>"); ?></p>
      </p>
      
    </div>
    <br class="clear" />
  </div>
  </div>
  </div>



