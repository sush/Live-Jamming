<div class="wrapper col2">
<div id="breadcrumb">
</div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col3">
<div id="container">
<div id="comments">
  <h2><?php echo __('article_page_title');?></h2>
  <ul class="commentlist">
    <?php $i=0;?>
    <?php foreach($articles as $article):?>
    <?php if ($i%2 == 0) echo '<li class="comment_even">'; else echo '<li class="comment_odd">';?>
    <div class="author"><img class="avatar" src="images/demo/avatar.gif" width="32" height="32" alt="" /><span class="name"><a href="#"><?php echo $article['Article']['title'];?></a></span></div>
    <div class="submitdate"><a href="#"><?php echo $article['Article']['date'];?></a></div>
    <p><?php echo $article['Article']['content'];?></p>
    </li>
    <?php $i++;?>
    <?php endforeach;?>
  </ul>
</div>
</div>
<br class="clear" />
</div>
</div>

