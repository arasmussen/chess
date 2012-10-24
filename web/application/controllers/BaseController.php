<?php

abstract class BaseController extends CI_Controller {
  private
    $pageName;

  public function __construct($page) {
    parent::__construct();
    $this->page = $page;
  }

  public function pre() {
    if ($this->tank_auth->is_logged_in()) {
      $data['is_logged_in'] = true;
      $data['username'] = 'asdf';
    } else {
      $data['is_logged_in'] = false;
    }

    $data['page'] = $this->page;

    $this->load->view('header', $data);
  }

  public function post() {
    $this->load->view('footer');
  }
}
