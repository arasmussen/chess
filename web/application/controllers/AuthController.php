<?php
require_once('BaseController.php');

abstract class AuthController extends BaseController {
  private
    $user_id,
    $username;

  public function __construct($page) {
    parent::__construct($page);

    if (!$this->tank_auth->is_logged_in()) {
      header('Location: /');
    }

    $this->user_id = $this->tank_auth->get_user_id();
    $this->username = $this->tank_auth->get_username();
  }

  protected function getUserId() {
    return $this->user_id;
  }

  protected function getUsername() {
    return $this->username;
  }
}
