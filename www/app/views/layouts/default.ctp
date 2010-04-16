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
 * @subpackage    cake.cake.libs.view.templates.layouts
 * @since         CakePHP(tm) v 0.10.0.1076
 * @license       MIT License (http://www.opensource.org/licenses/mit-license.php)
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="EN" lang="EN" dir="ltr">
<head profile="http://gmpg.org/xfn/11">

<?php echo $this->Html->charset(); ?>
<title>
Live-Jamming
<?php echo $title_for_layout; ?>
</title>
<?php
echo $this->Html->meta('icon');
echo $this->Html->css('layout');
echo $scripts_for_layout;
?>
</head>
<body id="top">
<div class="wrapper col1">
<div id="header">
<div class="language">
  <?php echo $this->Html->link($html->image("gb.png", array("alt" => "Change to english")), array('language'=>'en'), array('escape' => false)); ?>
  <?php echo $this->Html->link($html->image("fr.png", array("alt" => "Change to french")), array('language'=>'fr'), array('escape' => false)); ?>
</div>
<div id="logo">
  <?php echo $this->Html->image('/img/logo.png', array('alt' => 'live-jamming', 'url' => 'http://www.live-jamming.com'));?>
  <?php
  if ($userIsConnected)
  echo $this->element('welcome')
  ?>
</div>
<?php
if($userIsConnected)
echo $this->element('menu/connected');
else
echo $this->element('menu/default');
?>
<br class="clear" />
</div>

</div>
<?php echo $content_for_layout; ?>
<div class="wrapper col5">
<div id="copyright">
  <p class="fl_left">Copyright &copy; 2010 - All Rights Reserved - <a href="#">Live-Jamming</a></p>
  <br class="clear" />
</div>
</div>
<?php echo $this->element('sql_dump'); ?>
</body>
</html>
