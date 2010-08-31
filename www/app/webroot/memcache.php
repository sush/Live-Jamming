<?php
$memcache = new Memcache;
$memcache->connect('localhost:11211') or die("Could not connect");
$key = md5('42data');
for($k =0;$k<5;$k++){
  $data =$memcache->get($key);
  if($data == NULL){
    $data = array();
    echo "Expensive query";
    for ($i=0; $i<100;$i++){
      for($j=0;$j<10;$j++){
	$data[$i][$j] = 42;
      }
    }
    $memcache->set($key,$data,0,3600);
  }else{
    echo "cached";
  }
 }

?>