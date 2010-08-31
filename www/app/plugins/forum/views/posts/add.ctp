
<?php // Crumbs
$html->addCrumb($topic['ForumCategory']['Forum']['title'], array('controller' => 'home', 'action' => 'index'));
if (!empty($topic['ForumCategory']['Parent']['slug'])) {
	$html->addCrumb($topic['ForumCategory']['Parent']['title'], array('controller' => 'categories', 'action' => 'view', $topic['ForumCategory']['Parent']['slug']));
}
$html->addCrumb($topic['ForumCategory']['title'], array('controller' => 'categories', 'action' => 'view', $topic['ForumCategory']['slug']));
$html->addCrumb($topic['Topic']['title'], array('controller' => 'topics', 'action' => 'view', $topic['Topic']['slug'])); ?>

<div class="forumHeader">
	<h2><?php __d('forum', 'Post Reply'); ?></h2>
</div>

<?php echo $form->create('Post', array('url' => array('controller' => 'posts', 'action' => 'add', $id, $quote_id))); ?>

<div class="input textarea">
	<?php echo $form->label('content', __d('forum', 'Content', true)); ?>

	<div id="textarea">
		<?php echo $form->input('content', array('type' => 'textarea', 'rows' => 15, 'label' => false, 'div' => false)); ?>
	</div>

	<span class="clear"><!-- --></span>
	<?php echo $this->element('markitup', array('textarea' => 'PostContent')); ?>
</div>

<div class="input ac">
	<strong><?php __d('forum', 'Allowed Tags'); ?>:</strong> [b], [u], [i], [img], [url], [email], [code], [align], [list], [li], [color], [size], [quote]
</div>

<?php echo $form->end(__d('forum', 'Post', true)); ?>

<?php // Topic review
if (!empty($review)) { ?>
<div class="forumWrap">
    <h3><?php __d('forum', 'Topic Review - Last 10 Replies'); ?></h3>
    
    <div id="topicReview">
        <table class="table" cellspacing="0">
        
        <?php foreach ($review as $post) { ?>
        <tr class="altRow" id="post_<?php echo $post['Post']['id']; ?>">
            <td colspan="2" class="ar"><?php echo $time->niceShort($post['Post']['created'], $cupcake->timezone()); ?></td>
        </tr>
        <tr>
            <td valign="top" style="width: 25%">
                <h4><?php echo $html->link($post['User']['login'], array('controller' => 'users', 'action' => 'profile', $post['User']['id'])); ?></h4>
                <strong><?php __d('forum', 'Joined'); ?>:</strong> <?php echo $time->niceShort($post['User']['created'], $cupcake->timezone()); ?>
            </td>
            <td valign="top"><?php $decoda->parse($post['Post']['content']); ?></td>
        </tr>
        <?php } ?>
        
        </table>
  	</div>      
</div>  
<?php } ?>