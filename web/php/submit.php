<?php
	$sql = urldecode($_GET['sql']); //解码

	//echo $sql;
	$filename = "../xml/data.xml";
	if (file_exists($filename)) {  //删除旧文件
		unlink($filename);
	}

	set_time_limit(0);  
	$host = "127.0.0.1";  
	$port = 10000;  
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)or die("Could not create socket\n");
	$connection = socket_connect($socket, $host, $port) or die("Could not connect server\n");
	socket_set_block($socket);

	$result = "";
	socket_write($socket, $sql);
	while(($buff = socket_read($socket, 1024)) != "") {
		$result .= $buff;
		$reslen = strlen($result);
		if($result[$reslen - 1] == 'd'	&& $result[$reslen - 2] == 'n' && $result[$reslen - 3] == 'e') {
			$result = substr($result, 0, $reslen - 3);	
			break;	
		}
	}
	socket_close($socket);  

    //创建xml文件
    	$data = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>";
	$data .= "<all>";
	$data .= $result;
	$data .= "</all>"; 
	
	$xml = new SimpleXmlElement($data);
    
	echo $xml;	
	//写入数据
	$file = fopen($filename, 'w');
	fwrite($file, $xml->asXML());
	fclose($file);
?>
