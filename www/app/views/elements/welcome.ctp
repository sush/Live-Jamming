<div class="welcome_message">
  <span><?php echo __('user_connexion_welcome_message')?> </span><span class="welcome_login"><?php echo $user['login'];?></span>
  <?php
  if($user['group_id'] == GROUP_ADMIN)
  echo $html->link(': admin', '/admin');
  ?>
</div>
    