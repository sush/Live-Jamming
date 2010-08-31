<?php echo $html->script(array('jquery-1.4.1.min',
'jquery.jcarousel.pack',
'jquery.jcarousel.setup'),
array('inline' => false)); ?>
<div class="wrapper col2">
  <div id="featured_slide">
    <div id="featured_content">
      <ul>
        <li><img src="img/home/install_it.jpg" alt="" />
          <div class="floater">
            <p><?php __('home_caroussel_title_1');?></p>
          </div>
        </li>
        <li><img src="img/home/plug_it.jpg" alt="" />
          <div class="floater">
            <p><?php __('home_caroussel_title_2');?></p>
          </div>
        </li>
        <li><img src="img/home/play_it.jpg" alt="" />
          <div class="floater">
            <p><?php __('home_caroussel_title_3');?></p>
          </div>
        </li>
      </ul>
    </div>
    <a href="javascript:void(0);" id="featured-item-prev"><img src="img/prev.png" alt="" /></a> <a href="javascript:void(0);" id="featured-item-next"><img src="img/next.png" alt="" /></a> </div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col3">
  <div id="container">
    <div class="homepage">
      <ul>
	<li>
	  <h2><img src="img/icons/news.png" alt="" /><?php echo __('home_page_title_news',true);?></h2>
	  <p class="home">
	    <?php foreach($lastNews as $lastNews): ?>
	    <span id="article_title"><?php echo $lastNews['Article']['title']; ?></span>
	<span id="article_date">
	<?php $timestamp = strtotime($lastNews['Article']['date']);
	$format = (Configure::read('Config.language') == 'fre') ? "%d-%m-%Y" : "%Y-%m-%d";
	echo strftime($format, $timestamp); ?>
	</span><br/>
	    <span><?php echo $text->truncate($lastNews['Article']['content'], 250, array('ending' => '...', 'exact' => false)); ?></span>
	    <?php endforeach;?>
	  </p>
	  <p class="readmore">
	    <?php echo $this->Html->link(__('read_more', true), array('controller' => 'articles','action' => 'display'),array('escape' => false));?>
	  </p>
	</li>
        <li>
	  <h2><img src="img/icons/last_record.png" alt="" /><?php echo __('home_page_title_last_records',true);?></h2>
	<p class="home">
	<?php if (sizeof($lastRecords) != 0) { ?>
	<?php foreach($lastRecords as $record): ?>
	    <?php echo date('m/d/Y',strtotime($record['Record']['date']));?> <a href="#"><?php echo $record['Record']['title'];?></a> <i id="duration">(<?php echo $record['Record']['duration'];?>)</i><br/>
	    <?php endforeach;?>
	  <p class="readmore">
	    <?php echo $this->Html->link(__('all_records', true), array('controller' => 'records','action' => 'display'),array('escape' => false));?>
	<?php } else { ?>
	<?php echo __('no_records',true);?>
	<?php }?>
	  </p>
        </li>
        <li class="last">
	  <h2><img src="img/icons/how_to.png" alt="" /><?php echo __("home_page_how_to_title",true)?></h2>
	  <p class="home"><?php echo __("home_page_how_to_text",true);?></p>
	  <p class="readmore">
	    <?php echo $this->Html->link(__("home_page_how_to_button",true)." &raquo;", array('controller' => 'tutorials'),array('escape' => false));?>
	  </p>
	</li>
      </ul>
      <br class="clear" />
    </div>
  </div>
</div>
<!-- ####################################################################################################### -->
<div class="wrapper col4">
  <div id="footer">
    <br class="clear" />
  </div>
</div>
