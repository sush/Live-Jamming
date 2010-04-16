<div id="topnav">
  <ul>
    <li><?php echo $this->Html->link(__('topnav_menu_1', true), '/');?></li>
    <li><?php echo $this->Html->link(__('topnav_menu_2', true), array('controller' => 'pages','action' => 'display', 'home'));?></li>
    <li><?php echo $this->Html->link(__('topnav_menu_3', true), array('controller' => 'pages','action' => 'display', 'home'));?></li>
    <li><?php echo $this->Html->link(__('topnav_menu_6', true), array('controller' => 'pages','action' => 'display', 'home'));?></li>
    <li><?php echo $this->Html->link(__('user_account', true), array('controller' => 'users', 'action' => 'account'));?>
    <ul>
      <li><?php echo $this->Html->link(__('user_my_account', true), array('controller' => 'users', 'action' => 'account'));?></li>
      <li><?php echo $this->Html->link(__('user_change_password', true), array('controller' => 'users', 'action' => 'changepassword'));?></li>
      <li><?php echo $this->Html->link(__('user_my_records', true), array('controller' => 'users', 'action' => 'records'));?></li>
    </ul>
  </li>
  <li><?php echo $this->Html->link(__('user_logout', true), array('controller' => 'users', 'action' => 'logout'));?></li>
  </ul>
</div>