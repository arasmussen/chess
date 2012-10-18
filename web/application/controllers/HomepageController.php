<?php

class HomepageController extends CI_Controller {
  public function index() {
    if ($this->tank_auth->is_logged_in()) {
      $data['is_logged_in'] = true;
      $data['username'] = 'asdf';
    } else {
      $data['is_logged_in'] = false;
    }

    $this->load->view('header', $data);
    $this->load->view('homepage');
    $this->load->view('footer');
  }
}

?>
