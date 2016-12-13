<?php

$wechatObj = new clientGet();
if(isset($_GET["dm"])) $wechatObj->reMsg();

class clientGet
{
	public function reMsg()
    {
		// echo "hah";
		$pdo = new PDO("mysql:host=localhost;dbname=weixin", "root", "***");
		$sql1 = "select * from wenben limit 1;";
		$echoStr = $pdo->query($sql1)->fetch();
		if($echoStr) echo $echoStr[0];
		else echo "";
		$sql2 = "delete from wenben where text = '$echoStr[0]';";
		$pdo->exec($sql2);
    }
}

?>