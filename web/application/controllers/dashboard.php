<?php
require_once('AuthController.php');

class dashboard extends AuthController {
  public function __construct() {
    parent::__construct('dashboard');
  }

  public function index() {
    $this->pre();

    $this->load->view('dashboard/dashboard');

    $this->post();
  }
}
