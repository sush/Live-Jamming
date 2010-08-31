<?php
e($rss->items($articles,'sortieRSS'));

function sortieRSS($article){
return array(
'title' => utf8_encode($article['Article']['title']),
'link' => 'http://www.live-jamming.com/articles/display',
'description' => utf8_encode($article['Article']['content']),
'pubDate' => $article['Article']['date']
);
}
?>