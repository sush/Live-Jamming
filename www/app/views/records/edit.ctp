<div class="records form">
<?php echo $this->Form->create('Record');?>
	<fieldset>
 		<legend><?php printf(__('Edit %s', true), __('Record', true)); ?></legend>
	<?php
		echo $this->Form->input('id');
		echo $this->Form->input('title');
		echo $this->Form->input('date');
		echo $this->Form->input('path');
		echo $this->Form->input('duration');
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit', true));?>
</div>
<div class="actions">
	<h3><?php __('Actions'); ?></h3>
	<ul>

		<li><?php echo $this->Html->link(__('Delete', true), array('action' => 'delete', $this->Form->value('Record.id')), null, sprintf(__('Are you sure you want to delete # %s?', true), $this->Form->value('Record.id'))); ?></li>
		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Records', true)), array('action' => 'index'));?></li>
		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Record Participants', true)), array('controller' => 'record_participants', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(sprintf(__('New %s', true), __('Record Participant', true)), array('controller' => 'record_participants', 'action' => 'add')); ?> </li>
	</ul>
</div>