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

    $data = $this->tank_auth->create_user($username, $email, $password, true);
    if ($data !== null) {
      $this->sendActivationEmail($data);
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

  private function sendActivationEmail($data) {
    $to = $data['email'];
    $subject = 'Venzio Account Activation';
    $url =
      'http://www.venz.io/index.php/HomepageController/activate?username=' .
      $data['username'] .
      '&key=' .
      $data['new_email_key'];
    $message =
      '<html>' .
        '<head>' .
          '<title>Venzio Account Activation</title>' .
        '</head>' .
        '<body>' .
          '<p>Thanks for signing up for Venzio Chess AI!</p>' .
          '<p>Activate your account by clicking on ' .
            '<a href="' . $url . '">this link</a>.' .
          '</p>' .
        '</body>' .
      '</html>';

    $this->amazon_ses->to($to);
    $this->amazon_ses->from('arasmussen@katworks.com');
    $this->amazon_ses->subject($subject);
    $this->amazon_ses->message($message);
    $this->amazon_ses->send();
  }
}

?>
