define(['jquery'], function($) {
  return {
    login: function(username, password, callback) {
      $.ajax({
        type: 'POST',
        url: '/index.php/HomepageController/login',
        data: {username: username, password: password}
      }).success(function(request, response) {
        if (response === 'success') {
          callback(true);
        } else {
          callback(false);
        }
      });
    },

    register: function(email, username, password, callback) {
      $.ajax({
        type: 'POST',
        url: '/index.php/HomepageController/register',
        data: {email: email, username: username, password: password}
      }).success(function(request, response) {
        alert(response);
        if (response === 'success') {
          callback(true);
        } else {
          callback(false);
        }
      });
    }
  }
});
