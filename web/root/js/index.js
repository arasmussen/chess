requirejs(['jquery', 'auth'], function($, auth) {
  function loginFailed() {
    alert('login failed!');
  }

  function loginCallback(success) {
    if (success) {
      window.location.href = '/index.php/DashboardController/dashboard';
    } else {
      loginFailed();
    }
  }

  function initializeLogin() {
    $('#login form').bind('submit', function() {
      var username = $(this).find('input[name="username"]').val();
      var password = $(this).find('input[name="password"]').val();

      auth.login(username, password);
    });
  }

  function registerFailed() {
    alert('register failed!');
  }

  function registerCallback(success) {
    if (success) {
      window.location.href = '/index.php/HomepageController/activate';
    } else {
      registerFailed();
    }
  }

  function initializeRegister() {
    $('#register form').bind('submit', function() {
      var email = $(this).find('input[name="email"]').val();
      var username = $(this).find('input[name="username"]').val();
      var password = $(this).find('input[name="password"]').val();

      auth.register(email, username, password, registerCallback);
    });
  }

  $(function() {
    initializeLogin();
    initializeRegister();
  });
});
