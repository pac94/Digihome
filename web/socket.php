<?php

function sendToArduino($json)
{
	//error_reporting(E_ALL);
	$service_port = 9494;//getservbyname('www', 'tcp');
	$address = gethostbyname('localhost');
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	if ($socket === false)
	{
		$out = "{\"error\":\"socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\"}";
	}
	else
	{
		$result = socket_connect($socket, $address, $service_port);
		if ($result === false)
		{
	    		$out =  "{\"error\":\"socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\"}";
		}
		else
		{
			socket_write($socket, $json, strlen($json));
			$out = '';
			$out = socket_read($socket, 2048);
		}
	}
	socket_close($socket);
	return $out;
}
?>

