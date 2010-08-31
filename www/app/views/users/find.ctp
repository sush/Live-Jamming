<div class="wrapper col2">
<div id="breadcrumb">
</div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col3">
<div id="container">
  <?php echo $this->Session->flash(); ?>
  
<div id="userForm">
  <?php echo $form->create('User', array('url' => '/users/find'));?>
    <fieldset style="background-color:#F9F9F9;">
  <legend><?php __('user_find_form_legend', false); ?></legend>
  <?php
  echo $form->input('login', array('div' => false, 'label' => __('user_register_form_login',true)));
  if($userIsConnected)
  echo $form->input('country_id', array('div' => false, 'default' => $user['country_id'], 'empty' => '-', 'label' => __('user_register_form_country',true)));
  else
  echo $form->input('country_id', array('div' => false, 'empty' => '-', 'label' => __('user_register_form_country',true)));
  echo $form->input('instrument_id', array('div' => false, 'empty' => '-', 'label' => __('user_register_form_instrument',true)));
  echo $form->input('level_id', array('div' => false, 'empty' => '-', 'label' => __('user_register_form_level',true)));
  echo $form->submit(__('Search', true), array('div' => false));
  ?>
  <br/>
  </fieldset>
  <?php echo $form->end();?>
</div>

 
<div id="comments">
  <br/>
  <h2><?php echo sizeof($members);?> Live-Jammer<?php echo (sizeof($members) > 1)?'s':'';?></h2>
<div class="paginate">
  <?php
  if (sizeof($members) != 0){
  echo '« '; echo $paginator->prev(__('user_paginate_previous',true) , null, null, array('class' => 'disabled'));
  echo ' ';
  echo $paginator->numbers();
  echo ' ';
  echo $paginator->next(__('user_paginate_next',true), null, null, array('class' => 'disabled'));
  echo ' »';
  }
  ?>
  </div>

  <ul class="commentlist">
    <?php $i = 0;?>
    <?php foreach($members as $member):?>
    <?php if ($i%2 == 0) echo '<li class="comment_even">'; else echo '<li class="comment_odd">';?>
    <div class="author">
      <img class="avatar" src='/img/icons/music/<?php echo $member['User']['instrument_id']?>.png' width="105" height="105" alt="<?php echo $instruments[$member['User']['instrument_id']];?>" />
      <span class="name"><?php echo $this->Html->link($member['User']['login'],array('controller' => 'users', 'action' => 'profil', $member['User']['login']))?> </span>
    </div>
    <div class="submitdate"><?php echo __('find_page_member_since',true).' '.$member['User']['created'];?></div>
    <p> <b><?php __('user_find_form_country');?>:</b> <?php echo $member['Country']['country'];?> </p>
    <p> <b><?php __('user_find_form_instrument');?>:</b> <?php echo $instruments[$member['User']['instrument_id']];?> </p>
    <p> <b><?php __('user_find_form_level');?>:</b> <?php echo $levels[$member['User']['level_id']];?> </p>
    <?php if(sizeof($member['Record']) != 0) {?>
    <p> <a href="/users/profil/<?php echo $member['User']['login']?>"><b><?php echo sizeof($member['Record']);?> <?php __('user_find_form_record');?><?php echo (sizeof($member['Record']) > 1)?'s':''; ?></b></a></p>
    <?php } else {?>
    <p><b>
    <?php echo __('user_find_form_no_record');?>
    </b></p>
    <?php }?>
    <p><i><?php echo $member['User']['description'];?></i></p>
    </li>
    <?php $i++;?>
    <?php endforeach;?>        
  </ul>
  <!-- Affiche le nombre de pages -->

  <!-- Affiche les liens des pages précédentes et suivantes -->
  <div class="paginate">
  <?php
    if (sizeof($members) != 0){
    echo '« '; echo $paginator->prev(__('user_paginate_previous',true) , null, null, array('class' => 'disabled'));
    echo ' ';
    echo $paginator->numbers();
    echo ' ';
    echo $paginator->next(__('user_paginate_next',true), null, null, array('class' => 'disabled'));
    echo ' »';
    }
  ?>
  </div>
</div>

<br class="clear" />
</div>
</div>

