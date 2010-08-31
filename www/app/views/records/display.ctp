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
  <h1><?php echo __('record_page_title',true);?>
  <span style="float:right;">
  <object type="application/x-shockwave-flash" name="dewplayer" id="dewplayer" data="/swf/dewplayer.swf" width="200" height="20">
  <param name="movie" value="/swf/dewplayer.swf"/>
  <param name="FlashVars" value="mp3=&javascript=on"/>
  </object>
  </span></h1>
  <table summary="My Records" cellpadding="0" cellspacing="0">
    <thead>
      <tr>
	<th><?php echo __('record_page_tab_name',true);?></th>
	<th><?php echo __('record_page_tab_date',true);?></th>
	<th><?php echo __('record_page_tab_participant',true);?></th>
	<th><?php echo __('record_page_tab_length',true);?></th>
      </tr>
    </thead>
    <tbody>
      <?php $i = 0;?>
      <?php foreach($records as $record): ?>
      <?php if ($i%2 == 0) echo '<tr class="light">'; else echo '<tr class="dark">';?>
	<td><?php echo $this->Html->link($this->Html->tag('span',$record['Record']['title'], array('class' => 'record_name')),'#',  array('value' => $record['Record']['path'],'class' => 'play', 'escape' => false));?></td>
	<td><?php echo $record['Record']['date'];?></td>
	<td><?php foreach($recordParticipant[$i]['User'] as $participant):?>
	  <?php echo $this->Html->link($participant['login'],array('controller' => 'users', 'action' => 'profil', $participant['login']));?> 
	  <?php endforeach;?></td>
	  <td><?php echo $record['Record']['duration'];?></td>
	</tr>
	<?php $i++;?>
	<?php endforeach;?>   
      </tbody>
    </table>
    <br class="clear" />
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
