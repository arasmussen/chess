define(['jquery'], function($) {
  function isValidEmail(email) {
    var re = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(email);
  }

  return {
    login: function(username, password, callback) {
      if (username.length < 4 || username.length > 20) {
        callback('username');
      } else if (password.length < 4 || password.length > 20) {
        callback('password');
      } else {
        $.ajax({
          type: 'POST',
          url: '/home/login',
          data: {username: username, password: password}
        }).success(callback);
      }
    },

    register: function(email, username, password, callback) {
      if (!isValidEmail(email)) {
        callback('email');
      } else if (password.length < 4 || password.length > 20) {
        callback('password');
      } else if (username.length < 4 || username.length > 20) {
        callback('username');
      } else {
        $.ajax({
          type: 'POST',
          url: '/home/register',
          data: {email: email, username: username, password: password}
        }).success(callback);
      }
    }
  }
});
