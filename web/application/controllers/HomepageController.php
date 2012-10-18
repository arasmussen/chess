<?php

class HomepageController extends CI_Controller {
  public function index() {
    $this->load->view('header');
    $this->load->view('homepage');
    $this->load->view('footer');
  }
}

?>
