<?php echo $html->script(array('jquery-1.4.1.min','swfobject','play'), array('inline' => false));?>
<div class="wrapper col2">
<div id="breadcrumb">
</div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col3">
<div id="container">
  <?php echo $this->Session->flash(); ?>
<div id="content">
<h1>My records
<span style="float:right;">
<object type="application/x-shockwave-flash" name="dewplayer" id="dewplayer" data="/swf/dewplayer.swf" width="200" height="20">
<param name="movie" value="/swf/dewplayer.swf"/>
<param name="FlashVars" value="mp3=&javascript=on"/>
</object>
</span>
</h1>
  <?php if(sizeof($records) != 0){ ?>
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
      <?php foreach($records as $record): ?>
      <?php if ($i%2 == 0) echo '<tr class="light">'; else echo '<tr class="dark">';?>
	<td><?php
	  echo $this->Html->link($this->Html->tag('span',$record['Record']['title'], array('class' => 'record_name')),'#',array('value' => $record['Record']['path'],'class' => 'play', 'escape' => false));
	  ?>
	</td>
	  <td><?php echo $record['Record']['date'];?></td>
	  <td><?php foreach($record['User'] as $participant): ?>
	    <?php if($participant['login'] != $_SESSION['Auth']['User']['login']) { ?>
	    <?php echo $this->Html->link($participant['login'],array('controller' => 'users', 'action' => 'profil', $participant['login']));}?> 
	    <?php endforeach;?></td>
	    <td><?php echo $record['Record']['duration'];?></td>
	  </tr>
	  <?php $i++;?>
	  <?php endforeach;?>   
	</tbody>
      </table>
      <?php }
      else{echo 'No Record';}
      ?>

  
  <br class="clear" />
</div>

<?php echo $this->element('last_register'); ?>

<br class="clear" />
</div>
</div>
