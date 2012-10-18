<?php
require_once('PageController.php');

class HomepageController extends PageController {
  public function index() {
    $this->load->view('homepage');
  }
}

?>
