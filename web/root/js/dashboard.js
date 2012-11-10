requirejs(['jquery'], function($) {
  function initializeUpload() {
    $('.uploadBot form').bind('submit', onUploadSubmit);
  }

  function uploadError(type) {
    if (type == 'filename') {
      alert('Please upload a tar, tar.gz, tgz, or zip file');
    }
  }

  function onUploadSubmit(e) {
    var pattern = /[a-zA-Z0-9]+\.(tar|tar\.gz|tgz|zip)$/i;
    var filename = $(this).find('input[type="file"]').val();

    if (!pattern.test(filename)) {
      uploadError('filename');
      e.preventDefault();
    }
  }

  $(function() {
    initializeUpload();
  });
});
