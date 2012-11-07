requirejs(['jquery', 'auth'], function($, auth) {
  function loginFailed(reason) {
    if (reason == 'username') {
      $('#login form input[name="username"]').addClass('failed');
    } else if (reason == 'password') {
      $('#login form input[name="password"]').addClass('failed');
    } else if (reason == 'failed') {
      $('#login form input[name="username"]').addClass('failed');
      $('#login form input[name="password"]').addClass('failed');
    }
  }

  function loginCallback(response) {
    if (response == 'success' || response == 'already logged in') {
      window.location.href = '/dashboard';
    } else if (response == 'needs to activate') {
      window.location.href = '/home/activate';
    } else if (response == 'wrong username/password') {
      loginFailed('failed');
    }
  }

  function initializeLogin() {
    $('#login form').bind('submit', function() {
      var username = $(this).find('input[name="username"]').val();
      var password = $(this).find('input[name="password"]').val();

      if (username.length < 4 || username.length > 20) {
        loginFailed('username');
      } else if (password.length < 4 || password.length > 20) {
        loginFailed('password');
      } else {
        auth.login(username, password, loginCallback);
      }
    });
  }
