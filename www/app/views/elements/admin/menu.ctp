<div id="menu" >
  <ul class="menu">
    <li class="parent"><?php echo $this->Html->link($this->Html->tag('span','Users'), array('controller' => 'users', 'prefix' => 'admin'),array('escape' => false));?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_download', true)), array('controller' => 'downloads'), array('escape' => false));?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_search', true)), array('controller' => 'users','action' => 'find'),array('escape' => false));?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_register', true)), array('controller' => 'users','action' => 'register'),array('escape' => false));?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span','Login'), array('controller' => 'users','action' => 'login'),array('escape' => false));?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_about', true)), array('controller' => 'pages','action' => 'display', 'home'),array('escape' => false));?></li>
    <li class="last"><?php echo $this->Html->link($this->Html->tag('span', 'Forum'), array('plugin' => 'forum', 'controller' => 'home'),array('escape' => false));?></li>
  </ul>
</div>
