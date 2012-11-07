<?php
require_once('BaseController.php');

class home extends BaseController {
  public function __construct() {
    parent::__construct('index');
  }

  // homepage
  public function index() {
    $this->pre();

    $this->load->view('home/register');

    $this->post();
  }

  // user just registered or tried to log in and needs to activate
  public function sent() {
    $this->pre();

    $this->load->view('home/sent');

    $this->post();
  }

  // user clicked on the activate link in their email
  public function activate() {
    $uid = $this->input->get('uid');
    $key = $this->input->get('key');
    if ($this->tank_auth->activate_user($uid, $key)) {
      $this->tank_auth->logout();
      header('Location: /home/activated');
    } else {
      $this->pre();
      $this->load->view('home/activate');
      $this->post();
    }
  }

  // user successfully activated their account
  public function activated() {
    $this->pre();

    $this->load->view('home/activated');

    $this->post();
  }

  public function logout() {
    $this->tank_auth->logout();
    header('Location: /');
  }

  // ajax endpoint for logging in
  public function login() {
    $this->form_validation->set_rules('username', 'username', 'trim|required|xss_clean|min_length['.$this->config->item('username_min_Length', 'tank_auth').']|max_length['.$this->config->item('username_max_length', 'tank_auth').']|alpha_dash');
    $this->form_validation->set_rules('password', 'password', 'trim|required|xss_clean|min_length['.$this->config->item('password_min_Length', 'tank_auth').']|max_length['.$this->config->item('password_max_length', 'tank_auth').']|alpha_dash');

    if ($this->tank_auth->is_logged_in()) {
      echo 'already logged in';
    } else if ($this->tank_auth->is_logged_in(false)) {
      echo 'needs to activate';
    } else if (!$this->form_validation->run()) {
      echo 'invalid data';
    } else {
      $username = $this->form_validation->set_value('username');
      $password = $this->form_validation->set_value('password');

      if ($this->tank_auth->login($username, $password, true, true, false)) {
        echo 'success';
      } else {
        $error = $this->tank_auth->get_error_message();
        if (isset($errors['not_activated'])) {
          echo 'needs to activate';
        }
        echo 'wrong username/password';
      }
    }
  }

  // ajax endpoint for registering
  public function register() {
    $this->form_validation->set_rules('email', 'email', 'trim|required|xss_clean|valid_email');
    $this->form_validation->set_rules('username', 'username', 'trim|required|xss_clean|min_length['.$this->config->item('username_min_Length', 'tank_auth').']|max_length['.$this->config->item('username_max_length', 'tank_auth').']|alpha_dash');
    $this->form_validation->set_rules('password', 'password', 'trim|required|xss_clean|min_length['.$this->config->item('password_min_Length', 'tank_auth').']|max_length['.$this->config->item('password_max_length', 'tank_auth').']|alpha_dash');

    if ($this->tank_auth->is_logged_in()) {
      echo 'already logged in';
    } else if ($this->tank_auth->is_logged_in(false)) {
      echo 'already logged in, needs to activate';
    } else if (!$this->form_validation->run()) {
      echo 'invalid data';
    } else {
      $email = $this->form_validation->set_value('email');
      $username = $this->form_validation->set_value('username');
      $password = $this->form_validation->set_value('password');

      $data = $this->tank_auth->create_user($username, $email, $password, true);
      if ($data !== null) {
        $this->sendActivationEmail($data);
        echo 'success';
      } else {
        $error = $this->tank_auth->get_error_message();
        if (array_key_exists('username', $error)) {
          echo 'username in use';
        } else if (array_key_exists('email', $error)) {
          echo 'email in use';
        } else {
          echo 'invalid data';
        }
      }
    }
  }

  // private function that sends activation email
  private function sendActivationEmail($data) {
    $to = $data['email'];
    $subject = 'Venzio Account Activation';
    $url =
      'http://www.venz.io/home/activate?uid=' .
      $data['user_id'] .
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
    $this->amazon_ses->from('no-reply@venz.io');
    $this->amazon_ses->subject($subject);
    $this->amazon_ses->message($message);
    $this->amazon_ses->send();
  }
}

?>
