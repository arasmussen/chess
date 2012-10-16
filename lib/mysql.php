<?php

function connect($access) {
  if ($access == 'read') {
    $user = 'chess_r';
    $password = getenv('CHESS_READ_PASSWORD');
  } else {
    $user = 'chess_w';
    $password = getenv('CHESS_WRITE_PASSWORD');
  }

  $db = mysql_connect('localhost', $user, $password);
  mysql_select_db('Chess');
  return $db;
}

?>
