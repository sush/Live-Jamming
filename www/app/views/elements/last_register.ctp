<div id="column">
<div class="last_register">
  <div id="title"><p><?php e(__('last_subscriber', true))?><p></div>
  <div id="members">
  <?php $members = $this->requestAction('/users/getLastMembers');?>

  <?php foreach($members AS $member): ?>
    <span id="name">
    <img src="/img/icons/music/tiny/<?php echo $member['User']['instrument_id']?>.png" title="">
    <?php echo $this->Html->link($member['User']['login'], '/users/profil/'.$member['User']['login']); ?>
    </span>
    <span id="date">
    <?php $timestamp = strtotime($member['User']['created']);
    $format = (Configure::read('Config.language') == 'fre') ? "%d-%m-%Y" : "%Y-%m-%d";
    echo strftime($format, $timestamp); ?>
    </span><br/>
  <?php endforeach; ?>
    
  </div>
</div>
</div>