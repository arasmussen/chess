<!DOCTYPE html>
<html>
  <head>
    <title>Chess AI</title>
    <link rel="stylesheet" type="text/css" href="/css/reset.css" />
    <script type="text/javascript" src="/js/jquery-1.7.2.min.js"></script>
    <meta http-equiv="content-type" content="text/html;charset=utf-8">
  </head>
  <body>
    <div id="center">
      <div id="header">
        <?php
          if ($is_logged_in) {
            echo 'Logged in as: ' . $username . "\n";
          } else {
            echo 'Not logged in.' . "\n";
          }
        ?>
      </div>
      <div id="page">
