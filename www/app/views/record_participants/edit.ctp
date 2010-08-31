<div class="recordParticipants form">
<?php echo $this->Form->create('RecordParticipant');?>
	<fieldset>
 		<legend><?php printf(__('Edit %s', true), __('Record Participant', true)); ?></legend>
	<?php
		echo $this->Form->input('record_id');
		echo $this->Form->input('user_id');
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit', true));?>
</div>
<div class="actions">
	<h3><?php __('Actions'); ?></h3>
	<ul>

		<li><?php echo $this->Html->link(__('Delete', true), array('action' => 'delete', $this->Form->value('RecordParticipant.id')), null, sprintf(__('Are you sure you want to delete # %s?', true), $this->Form->value('RecordParticipant.id'))); ?></li>
		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Record Participants', true)), array('action' => 'index'));?></li>
		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Records', true)), array('controller' => 'records', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(sprintf(__('New %s', true), __('Record', true)), array('controller' => 'records', 'action' => 'add')); ?> </li>
		<li><?php echo $this->Html->link(sprintf(__('List %s', true), __('Users', true)), array('controller' => 'users', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(sprintf(__('New %s', true), __('User', true)), array('controller' => 'users', 'action' => 'add')); ?> </li>
	</ul>
</div>