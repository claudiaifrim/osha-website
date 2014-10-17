<?php
error_reporting(E_ALL);
ini_set("display_errors", 1);
if(isset($_GET['lang']) && in_array($_GET["lang"], ["bg","cs","da","de","el","en","es","et","fi","fr","hr","hu","it","lb","lt","lv","mt","nl","no","pl","pt","ro","ru","sk","sl","sv","tr"])) {
	echo file_get_contents("./data/taxonomy." . $_GET["lang"] . ".json");
}
else {
	echo file_get_contents("/data/taxonomy.en.json");
}
?>