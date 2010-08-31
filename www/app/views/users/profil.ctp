<?php echo $html->script(array('jquery-1.4.1.min','swfobject','play'), array('inline' => false));?>

<div class="wrapper col2">
  <div id="breadcrumb">
  </div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col3">
<div id="container">
  <div id="comments">
  <ul class="commentlist">
    <li class="comment_even">
    <div class="author">
      <img class="avatar" src="/img/icons/music/<?php echo $member['User']['instrument_id']?>.png" width="105" height="105" alt="<?php echo $instruments[$member['User']['instrument_id']];?>" />
      <span class="name"><?php echo $member['User']['login'];?> </span>
    </div>
    <div class="submitdate">Member since <?php echo $member['User']['created'];?></div>
    <p> <b><?php __('user_find_form_country');?>:</b> <?php echo $member['Country']['country'];?> </p>
    <p> <b><?php __('user_find_form_instrument');?>:</b> <?php echo $instruments[$member['User']['instrument_id']];?> </p>
    <p> <b><?php __('user_find_form_level');?>:</b> <?php echo $levels[$member['User']['level_id']];?> </p>
    <p> <b><?php __('user_find_form_connexion_type');?>:</b> <?php echo $member['ConnectionType']['wording']?></p>
    <p><i><?php echo $member['User']['description'];?></i></p>
    </li>
  </ul>
<h1>My records
<span style="float:right;">
<object type="application/x-shockwave-flash" name="dewplayer" id="dewplayer" data="/swf/dewplayer.swf" width="200" height="20">
<param name="movie" value="/swf/dewplayer.swf"/>
<param name="FlashVars" value="mp3=&javascript=on"/>
</object>
</span>
</h1>
<?php if(sizeof($member['Record']) != 0){ ?>
<table summary="My Records" cellpadding="0" cellspacing="0">
  <thead>
    <tr>
      <th>Name</th>
      <th>Date</th>
      <th>Participants</th>
      <th>Length</th>
    </tr>
  </thead>
  <tbody>
    <?php $i = 0;?>
    <?php foreach($member['Record'] as $record): ?>
    <?php if ($i%2 == 0) echo '<tr class="light">'; else echo '<tr class="dark">';?>
      <td><?php echo $this->Html->link($this->Html->tag('span',$record['title'], array('class' => 'record_name')),'#',  array('value' => $record['path'],'class' => 'play', 'escape' => false));?></td>
      <td><?php echo $record['date'];?></td>
      <td><?php foreach($recordParticipant[$i]['User'] as $participant):?>
	<?php if($participant['login'] != $this->params['pass'][0]){ ?>
	<?php echo $this->Html->link($participant['login'],array('controller' => 'users', 'action' => 'profil', $participant['login']));}?> 
	<?php endforeach;?></td>
	<td><?php echo $record['duration'];?></td>
      </tr>
    <?php $i++;?>
    <?php endforeach;?>   
  </tbody>
</table>
<?php }
else{echo 'No Record';}
?></div>

<br class="clear" />
  </div>
</div>

