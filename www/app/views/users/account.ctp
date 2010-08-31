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
  <?php echo $this->Form->create('User', array('url' => '/users/account'));?>
  <fieldset>
  <legend><?php __('user_register_form_legend', false); ?></legend>
  <?php
  echo $this->Form->input('email',array('between' => '<br/>', 'label' =>__('user_register_form_email',true)));
  echo $this->Form->input('description',array('between' => '<br/>', 'label' =>__('user_register_form_description',true)));
  echo $this->Form->input('country_id',array('between' => '<br/>', 'label' =>__('user_register_form_country',true)));
  echo $this->Form->input('instrument_id',array('between' => '<br/>', 'label' =>__('user_register_form_instrument',true)));    
  echo $this->Form->input('level_id',array('between' => '<br/>', 'label' =>__('user_register_form_level',true)));
  echo $this->Form->input('connection_type_id',array('between' => '<br/>', 'label' =>__('user_register_form_connection',true)));
  echo $this->Form->input('gender_id',array('between' => '<br/>', 'label' =>__('user_register_form_gender',true)));
  echo $this->Form->input('id', array('type' => 'hidden'));
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

