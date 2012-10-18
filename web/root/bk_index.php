<!DOCTYPE html>
<html>
<head>
  <title>Title</title>
  <link rel="stylesheet" type="text/css" href="/css/styles.css" />
  <script type="text/javascript" src="/js/jquery-1.7.2.min.js"></script>
  <script type="text/javascript" src="/js/chess.js"></script>
</head>
<body>
  <div id="game">
    <table>
<?php
for ($i = 0; $i < 8; $i++) {
  echo '<tr>';
  for ($j = 0; $j < 8; $j++) {
    echo '<td>';
    if ($i < 2 || $i > 5) {
      echo '<img src="/img/black-king.png" />';
    }
    echo '</td>';
  }
  echo '</tr>';
}
?>
    </table>
  </div>
</body>
</html>
