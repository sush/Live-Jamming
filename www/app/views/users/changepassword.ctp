<div class="wrapper col2">
<div id="breadcrumb">
</div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col3">
<div id="container">
  <?php echo $this->Session->flash(); ?>
<div id="content">
<div id="userForm">
  <?php echo $this->Form->create('User', array('url' => '/users/changepassword'));?>
  <fieldset>
  <legend><?php __('user_register_form_legend', false); ?></legend>
  <?php
  echo $this->Form->input('old_password',array('between' => '<br/>', 'type' => 'password', 'label' =>__('user_register_form_old_password',true)));
  echo $this->Form->input('new_password',array('between' => '<br/>', 'type' => 'password', 'label' =>__('user_register_form_password',true)));
  echo $this->Form->input('confirm_password',array('between' => '<br/>', 'type' => 'password', 'label' =>__('user_register_form_confirm_password',true)));
  ?>
  <br/>
  </fieldset>
  <?php echo $this->Form->end(__('Submit', true));?>      
</div>

</div>
<div id="column">
<div class="subnav">
  <h2>Secondary Navigation</h2>
  <ul>
    <li><a href="#">Open Source Templates</a></li>
    <li><a href="#">Free CSS Templates</a>
    <ul>
      <li><a href="#">Free XHTML Templates</a></li>
      <li><a href="#">Free Website Templates</a></li>
    </ul>
  </li>
  <li><a href="#">Open Source Layouts</a>
  <ul>
    <li><a href="#">Open Source Software</a></li>
    <li><a href="#">Open Source Webdesign</a>
    <ul>
      <li><a href="#">Open Source Downloads</a></li>
      <li><a href="#">Open Source Website</a></li>
    </ul>
  </li>
</ul>
</li>
<li><a href="#">Open Source Themes</a></li>
</ul>
</div>
</div>
<br class="clear" />
</div>
</div>

