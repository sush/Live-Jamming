<?php
class Article extends AppModel {
	var $name = 'Article';

	var $actsAs = array('Translate' => array('title' => 'Title', 'content' => 'Content'));
}
?>