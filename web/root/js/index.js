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
    } else { // invalid data
      loginFailed('failed');
    }
  }

  function initializeLogin() {
    $('#login form input').bind('keyup', function() {
      $('#login form input').removeClass('failed');
    });
    $('#login form').bind('submit', function() {
      var username = $(this).find('input[name="username"]').val();
      var password = $(this).find('input[name="password"]').val();
      auth.login(username, password, loginCallback);
    });
  }

  function registerFailed(reason) {
    if (reason == 'email') {
      $('#register form input[name="email"]').addClass('failed');
    } else if (reason == 'username') {
      $('#register form input[name="username"]').addClass('failed');
    } else if (reason == 'password') {
      $('#register form input[name="password"]').addClass('failed');
    } else if (reason == 'confirm') {
      $('#register form input[name="confirm"]').addClass('failed');
    } else if (reason == 'unknown') {
      $('#register form input[name="email"]').addClass('failed');
      $('#register form input[name="username"]').addClass('failed');
      $('#register form input[name="password"]').addClass('failed');
      $('#register form input[name="confirm"]').addClass('failed');
    }
  }

  function registerCallback(response) {
    if (response == 'success' ||
        response == 'already logged in, needs to activate') {
      window.location.href = '/home/sent';
    } else if (response == 'already logged in') {
      window.location.href = '/dashboard';
    } else if (response == 'username in use') {
      registerFailed('username');
    } else if (response == 'email in use') {
      registerFailed('email');
    } else if (response == 'username' ||
               response == 'password' ||
               response == 'email') {
      registerFailed(response);
    } else { // invalid data
      registerFailed('unknown');
    }
  }

  function initializeRegister() {
    $('#register form input').bind('keyup', function() {
      $('#register form input').removeClass('failed');
    });
    $('#register form').bind('submit', function() {
      var email = $(this).find('input[name="email"]').val();
      var username = $(this).find('input[name="username"]').val();
      var password = $(this).find('input[name="password"]').val();
      var confirm = $(this).find('input[name="confirm"]').val();
      if (password != confirm) {
        registerFailed('confirm');
      }
      auth.register(email, username, password, registerCallback);
    });
  }

  $(function() {
    initializeLogin();
    initializeRegister();
  });
});
