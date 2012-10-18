<?php

abstract class PageController extends CI_Controller {
  public function __construct() {
    parent::__construct();
    $this->load->view('header');
  }

  public function __destruct() {
    $this->load->view('footer');
  }
}

?>
