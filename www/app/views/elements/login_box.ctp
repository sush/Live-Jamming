<div id="connexion_form">
  <?php echo $form->create('User', array('action' => 'login'));?>
  <table>
    <tr>
      <td><?php echo __('user_connexion_form_login',true); ?></td>
      <td><?php echo $form->input('connexion_login', array('div' => false, 'label' => false)); ?></td>
    </tr>
    <tr>
      <td><?php echo __('user_connexion_form_password',true); ?></td>
      <td><?php echo $form->input('connexion_password', array('div' => false, 'label' => false,'type' => 'password')); ?></td>
    </tr>
    <tr>
      <td></td>
      <td><?php echo $form->submit('Login', array('div' => false));?>
      </td>
    </tr>
  </table>
</div>
<?php echo $this->Session->flash('auth'); ?>