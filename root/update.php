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

$db = connect('read');
$query = 'SELECT * FROM Commands WHERE sent = FALSE';
$results = mysql_query($query);
$commands = array();
while ($row = mysql_fetch_array($results, MYSQL_ASSOC)) {
  array_push($commands, $row['command']);
}

output($commands);

?>
