<div class="connectionTypes form">
<?php echo $this->Form->create('ConnectionType');?>
	<fieldset>
 		<legend><?php printf(__('Edit %s', true), __('Connection Type', true)); ?></legend>
	<?php
		echo $this->Form->input('id');
		echo $this->Form->input('wording');
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit', true));?>
</div>
<div class="actions">
	<h3><?php __('Actions'); ?></h3>
	<ul>

		<li><?php echo $this->Html->link(__('Delete', true), array('action' => 'delete', $this->Form->value('ConnectionType.id')), null, sprintf(__('Are you sure you want to delete # %s?', true), $this->Form->value('ConnectionType.id'))); ?></li>
		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Connection Types', true)), array('action' => 'index'));?></li>
		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Users', true)), array('controller' => 'users', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(sprintf(__('New %s', true), __('User', true)), array('controller' => 'users', 'action' => 'add')); ?> </li>
	</ul>
</div>