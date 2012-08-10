<?php

header('Cache-Control: no-cache, must-revalidate');
header('Expires: Fri, 10 Aug 2012 00:00:00 GMT');
flush();

$counter = 0;
while (true) {
  echo $counter++;
  flush();
  sleep(1);
}

?>
