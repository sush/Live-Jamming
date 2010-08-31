
<div id="menu">
  <ul class="menu">
    <li class="parent"><?php echo $this->Html->link(__('topnav_menu_home', true), '/');?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_download', true)), array('controller' => 'downloads'),array('escape' => false));?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_search', true)), array('controller' => 'users','action' => 'find'),array('escape' => false));?></li>
    <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_user_account', true)), array('controller' => 'users', 'action' => 'account'),array('escape' => false));?>
    <div>
      <ul>
	<li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_user_my_account', true)), array('controller' => 'users', 'action' => 'account'),array('escape' => false));?></li>
	<li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_user_change_password', true)), array('controller' => 'users', 'action' => 'changepassword'),array('escape' => false));?></li>
	<li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_user_my_records', true)), array('controller' => 'users', 'action' => 'records'),array('escape' => false));?></li>
      </ul>
    </div>
  </li>
  <li><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_about', true)), array('controller' => 'pages','action' => 'display', 'home'),array('escape' => false));?></li>
  <li><?php echo $this->Html->link($this->Html->tag('span', 'Forum'), array('plugin' => 'forum', 'controller' => 'home'),array('escape' => false));?></li>
  <li class="last"><?php echo $this->Html->link($this->Html->tag('span',__('topnav_menu_user_logout', true)), array('controller' => 'users', 'action' => 'logout'),array('escape' => false));?></li>
  </ul>
</div>