<div class="wrapper col3">
  <div id="container">
    <div class="dlmain">
      <div class="dlexplanation">
	<?php echo $html->image('icons/windows.png', array('alt' => 'Live-Jamming Windows', 'class' => 'dlicons'));?>
	<h1>Live-Jamming pour Windows</h1>
	<p>English here</p>
	<br/>Pour plus d'informations, visitez la section <a href="#">"Tutorial"</a>.</p>
      </div>
      <div class="button">
	<?php echo $this->Html->link($this->Html->tag('span','T&eacute;l&eacute;charger'), array('controller' => 'downloads','action' => 'windows'), array('escape' => false));?><span class="version"><i>(Version 32bits)</i></span>
      </div>
    </div>

    <div class="dlmain">
      <div class="dlexplanation">
	<?php echo $html->image('icons/linux.png', array('alt' => 'Live-Jamming Linux', 'class' => 'dlicons'));?>
	<h1>Live-Jamming pour Linux</h1>
	<p>Uttellus pretium intesque volutpat malesuada curabitur convallisis non dui elit fring. 
	  Tortorconvallis felis pellus curabitur in lorem tur in et nisse curabitudin. 
	  Mollisfelit portis a nibh lacinia temper tincidunt tincidunt sagittis males sed. 
	  Sedplatea sed ut faucibus maurien sed vestas elis aliquam ulla nam. </p>
	<p>Aeneanelit fauctortor et sed netuer malesuada id consequat cras vitae non.
	  Uttellus pretium intesque volutpat malesuada curabitur convallisis non dui elit fring. 
	  Tortorconvallis felis pellus curabitur in lorem tur in et nisse curabitudin. 
	  Mollisfelit portis a nibh lacinia temper tincidunt tincidunt sagittis males sed. 
	  Sedplatea sed ut faucibus maurien sed vestas elis aliquam ulla nam. 
	  Aeneanelit fauctortor et sed netuer malesuada id consequat cras vitae non.
	<br/>Pour plus d'informations, visitez la section <a href="#">"Tutorial"</a>.</p>
      </div>
      <div class="button">
	<?php echo $this->Html->link($this->Html->tag('span','T&eacute;l&eacute;charger'), array('controller' => 'downloads','action' => 'unixboost140'), array('escape' => false));?><span class="version"><i>(Libboost1.40)</i></span>
	<?php echo $this->Html->link($this->Html->tag('span','T&eacute;l&eacute;charger'), array('controller' => 'downloads','action' => 'unixboost135'), array('escape' => false));?><span class="version"><i>(Libboost1.35)</i></span>
      </div>
      </p>
    </div>
    <br class="clear" />
  </div>
</div>

