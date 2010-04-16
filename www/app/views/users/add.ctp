<div class="users form">
<?php echo $this->Form->create('User');?>
	<fieldset>
 		<legend><?php printf(__('Add %s', true), __('User', true)); ?></legend>
	<?php
		echo $this->Form->input('pseudo');
		echo $this->Form->input('passwd');
		echo $this->Form->input('email');
		echo $this->Form->input('connected');
		echo $this->Form->input('description');
		echo $this->Form->input('town');
		echo $this->Form->input('country_id');
		echo $this->Form->input('level_id');
		echo $this->Form->input('connection_type_id');
		echo $this->Form->input('gender_id');
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit', true));?>
</div>
<div class="actions">
	<h3><?php __('Actions'); ?></h3>
	<ul>

		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Users', true)), array('action' => 'index'));?></li>
	</ul>
</div>