<?php
require_once('BaseController.php');

class HomepageController extends BaseController {
  public function __construct() {
    parent::__construct('index');
  }

  // homepage
  public function index() {
    $this->pre();

    $this->load->view('homepage');

    $this->post();
  }

  // user just registered or tried to log in and needs to activate
  public function activate() {
    $this->pre();

    $this->load->view('activate');

    $this->post();
  }

  // ajax endpoint for logging in
  public function login() {
    $username = $this->input->post('username');
    $password = $this->input->post('password');
    if ($this->tank_auth->login($username, $password, true, true, false)) {
      echo 'success';
    } else {
      echo 'failure';
    }
  }

  // ajax endpoint for registering
  public function register() {
    $email = $this->input->post('email');
    $username = $this->input->post('username');
    $password = $this->input->post('password');

    if (
      $this->tank_auth->create_user($username, $email, $password, true) !== null
    ) {
      echo 'success';
    } else {
      $error = $this->tank_auth->get_error_message();
      if (array_key_exists('username', $error)) {
        echo 'username exists';
      } else if (array_key_exists('email', $error)) {
        echo 'email exists';
      } else {
        echo 'invalid data';
      }
    }
  }
}

?>
