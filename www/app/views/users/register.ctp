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
<?php echo $this->Form->create('User');?>
  <fieldset>
  <legend><?php __('user_register_form_legend', false); ?></legend>
  <?php
  echo $this->Form->input('login',array('between' => '<br/>', 'label' =>__('user_register_form_login',true)));
  echo $this->Form->input('password',array('between' => '<br/>', 'label' =>__('user_register_form_password',true)));
  echo $this->Form->input('confirm_password',array('between' => '<br/>', 'type' => 'password','label' =>__('user_register_form_confirm_password',true)));
  echo $this->Form->input('email',array('between' => '<br/>', 'label' =>__('user_register_form_email',true)));
  echo $this->Form->input('description',array('between' => '<br/>', 'label' =>__('user_register_form_description',true)));
  echo $this->Form->input('country_id',array('between' => '<br/>', 'label' =>__('user_register_form_country',true)));
  echo $this->Form->input('instrument_id',array('between' => '<br/>', 'label' =>__('user_register_form_instrument',true)));
  echo $this->Form->input('level_id',array('between' => '<br/>', 'label' =>__('user_register_form_level',true)));
  echo $this->Form->input('connection_type_id',array('between' => '<br/>', 'label' =>__('user_register_form_connection',true)));
  echo $this->Form->input('gender_id',array('between' => '<br/>', 'label' =>__('user_register_form_gender',true)));
  ?>
  <br/>
  <img id="captcha" src="<?php echo $this->Html->url('/users/captcha_image');?>" alt="" />
  <a href="javascript:void(0);" onclick="javascript:document.images.captcha.src='<?php echo $html->url('/users/captcha_image');?>?' + Math.round(Math.random(0)*1000)+1">Reload image</a> 
  <?php echo $this->Form->input('captcha',array('between' => '<br/>', 'label' =>__('user_register_form_captcha',true)));?>
  </fieldset>

  <?php echo $this->Form->end(__('Submit', true));?>      
</div>
</div>
<?php echo $this->element('last_register'); ?>
    <br class="clear" />
  </div>
</div>

