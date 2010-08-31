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
	<div id="login_information">
	  <p>To log in, enter your login and your password and click on the log in button below.<br/>
	  The login and password field are case sensitive.</p>
	</div>
	<br/>
	<?php e($this->element('login_box')); ?>
	<br/>
	<div id="register_information">
	  <p style="text-align:center;"><b>You dont have any account?</b><br/> Click on the register button below to create one, it's free!</p>
	  <a href="/users/register"><div id="register_button">
	      <span id="button_name">Register</span>
	    </div>
	  </a>
	</div>
      </div>
    </div>
    <?php echo $this->element('last_register'); ?>
    <br class="clear" />
  </div>
</div>


