<!DOCTYPE html>
<html>
  <head>
    <title>Chess AI</title>
    <link rel="stylesheet" type="text/css" href="/css/reset.css" />
    <link rel="stylesheet" type="text/css" href="/css/styles.css" />
    <script type="text/javascript" src="/js/jquery-1.7.2.min.js"></script>
    <script type="text/javascript" src="/js/scripts.js"></script>
    <meta http-equiv="content-type" content="text/html;charset=utf-8">
  </head>
  <body>
    <div id="center">
      <div id="header">
        <div id="logo">
        </div>
        <?php if ($is_logged_in) { ?>
          <div id="profileLink">
            <a href="<?php echo "/profile/$username"; ?>">
              <?php echo $username; ?>
            </a>
          </div>
        <?php } else { ?>
          <div id="login">
            <form method="post" action="javascript:void(0)">
              <div id="loginEmail">
                <label>Email</label>
                <input type="text" name="email">
              </div>
              <div id="loginPassword">
                <label>Password</label>
                <input type="password" name="password">
              </div>
              <div id="loginButton">
                <input type="submit" value="Sign in">
              </div>
            </form>
          </div>
        <?php } ?>
      </div>
      <div id="page">
