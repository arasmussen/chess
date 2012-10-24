<?php
require_once('AuthController.php');

class DashboardController extends AuthController {
  public function __construct() {
    parent::__construct('dashboard');
  }

  public function dashboard() {
    $this->pre();

    $this->load->view('dashboard');

    $this->post();
  }
}
