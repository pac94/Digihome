<?php
require_once("socket.php");
echo sendToArduino('{"sensor":"led", "status":"on", "room":"chambre"}');
?>
