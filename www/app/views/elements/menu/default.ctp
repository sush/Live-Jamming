<div id="topnav">
  <ul>
    <li><?php echo $this->Html->link(__('topnav_menu_1', true), '/');?></li>
    <li><?php echo $this->Html->link(__('topnav_menu_2', true), array('controller' => 'pages','action' => 'display', 'home'));?></li>
    <li><?php echo $this->Html->link(__('topnav_menu_4', true), array('controller' => 'users','action' => 'register'));?></li>
    <li><?php echo $this->Html->link(__('topnav_menu_3', true), array('controller' => 'pages','action' => 'display', 'home'));?></li>
  </ul>
</div>
<div id="connexion_form">
  <?php
  echo $form->create('User', array('action' => 'login'));
  echo $form->input('connexion_login', array('between' => '<br/>','label' =>__('user_connexion_form_login',true),'class' => 'input_connexion'));
  echo $form->input('connexion_password', array('between' => '<br/>','label' =>__('user_connexion_form_password',true),'class' => 'input_connexion','type' => 'password'));
  echo $form->end('Login');
  echo $this->Session->flash('auth');
  ?>
</div>