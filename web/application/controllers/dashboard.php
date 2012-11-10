<?php
require_once('AuthController.php');

class dashboard extends AuthController {
  public function __construct() {
    parent::__construct('dashboard');

    $this->load->model('bots');
  }

  public function index() {
    $this->pre();

    $data['bots'] = $this->bots->getUsersBots($this->getUserId());
    $this->load->view('dashboard/dashboard', $data);

    $this->post();
  }

  // endpoint for when the user wants to create a bot
  public function upload() {
    $this->pre();

    $this->load->view('dashboard/upload');

    $this->post();
  }

  // user uploads bot name and source from dashboard/upload to here
  public function create() {
    // validate the bot name
    $bot_name = $this->getBotName();
    if ($bot_name === NULL) {
      header('Location: /dashboard/upload?failed=name');
      return; // for some reason it's not returning here
    }

    // create the directories if necessary (/web/bots/username/botname)
    $this->createDirectories($bot_name);

    // upload the files to this directory
    if (!$this->uploadFile($bot_name)) {
      header('Location: /dashboard/upload?failed=true');
      return; // not sure if here too
    }

    // extract
    if (!$this->extractFiles($bot_name)) {
      header('Location: /dashboard/upload?failed=true');
      return;
    }

    // insert into db
    $this->bots->createBot($this->getUserId(), $bot_name);

    header('Location: /dashboard/dashboard');
  }

  private function getBotName() {
    $this->form_validation->set_rules('name', 'name', 'trim|required|xss_clean|min_length[4]|max_length[25]');
    if ($this->form_validation->run()) {
      return $this->form_validation->set_value('name');
    }
    return NULL;
  }

  private function createDirectories($bot_name) {
    $user_dir = getenv('PHP_CHESS_ROOT') . '/web/bots/' . $this->getUsername();
    $bot_dir = $user_dir . '/' . $bot_name;

    if (!is_dir($user_dir)) {
      mkdir($user_dir, 0777);
    }
    if (!is_dir($bot_dir)) {
      mkdir($bot_dir, 0755);
    }
  }

  private function uploadFile($bot_name) {
    $path = getenv('PHP_CHESS_ROOT') . '/web/bots/' . $this->getUsername() . '/' . $bot_name;
    $config['upload_path'] = $path;
    $config['allowed_types'] = '*';
    $config['max_size'] = '1024';

    $this->load->library('upload', $config);

    return $this->upload->do_upload('source');
  }

  private function extractFiles($bot_name) {
    $data = $this->upload->data();
    $file = $data['full_path'];
    $path = $data['file_path'];
    $ext = $data['file_ext'];

    chmod($file, 0755);

    $file = escapeshellarg($file);
    $path = escapeshellarg($path);

    if ($ext === '.tar') {
      exec('tar --strip-components=1 -xvf ' . $file . ' -C ' . $path);
    } else if ($ext === '.tar.gz' || $ext == '.tgz') {
      exec('tar --strip-components=1 -zxvf ' . $file . ' -C ' . $path);
    } else if ($ext === '.zip') {
      exec('unzip ' . $file);
    } else {
      exec('rm -f ' . $file);
      return false;
    }

    exec('rm -f ' . $file);

    return true;
  }
}

?>
