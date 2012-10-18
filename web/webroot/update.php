<?php
$root = $_SERVER['DOCUMENT_ROOT'];
require_once("$root/../lib/mysql.php");

function output($commands) {
  $output = '';
  $num_commands = sizeof($commands);
  for ($i = 0; $i < $num_commands; $i++) {
    $command = $commands[$i];
    $output .= $command;
    if ($i < $num_commands - 1) {
      $output .= ',';
    }
  }
  echo $output;
}

$db = connect('write');
$query = 'SELECT * FROM Commands WHERE sent = FALSE';
$results = mysql_query($query);
$commands = array();

$num_commands = mysql_num_rows($results);
if ($num_commands == 0) {
  echo '';
  exit();
}

$query = 'UPDATE Commands SET sent = TRUE WHERE';

for ($i = 0; $i < $num_commands; $i++) {
  $row = mysql_fetch_array($results, MYSQL_ASSOC);
  array_push($commands, $row['command']);

  $query .= ' id = ' . $row['id'];
  if ($i < $num_commands - 1) {
    $query .= ' OR';
  }
}

mysql_free_result($results);

mysql_query($query);
output($commands);

mysql_close($db);

?>
