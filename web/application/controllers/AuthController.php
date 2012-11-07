<?php
require_once('BaseController.php');

abstract class AuthController extends BaseController {
  public function __construct($page) {
    parent::__construct($page);

    if (!$this->tank_auth->is_logged_in()) {
      header('Location: /');
    }
  }
}
