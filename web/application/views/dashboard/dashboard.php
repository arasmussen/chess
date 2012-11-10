<h1>Dashboard</h1>
<div id="bots">
  <h2>Bots</h2>
<?php

if (count($bots) == 0) {
  echo '<p>You have not uploaded any bots yet. Upload one <a href="/dashboard/upload">here</a>!</p>';
} else {
  echo '<table><tr><th>Name</th><th>Language</th></tr>';
  foreach ($bots as $bot) {
    echo '<tr>';
    echo '<td>' . $bot->name . '</td>';
    echo '<td>' . $bot->language . '</td>';
    echo '</tr>';
  }
  echo '</table>';
}

?>
</div>
