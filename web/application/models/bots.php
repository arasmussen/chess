<?php

class bots extends CI_Model {
  private
    $table_name = 'bots';

  function __construct() {
    parent::__construct();
  }

  function getBotById($bot_id) {
    $this->db->where('id', $bot_id);
    $query = $this->db->get($this->table_name);
    if ($query->num_rows() == 1) return $query->row();
    return NULL;
  }

  function getBotByName($user_id, $bot_name) {
    $this->db->where('user_id', $user_id);
    $this->db->where('name', $bot_name);
    $query = $this->db->get($this->table_name);
    if ($query->num_rows() == 1) return $query->row();
    return NULL;
  }

  function getUsersBots($user_id) {
    $this->db->where('user_id', $user_id);
    $query = $this->db->get($this->table_name);
    return $query->result();
  }

  function createBot($user_id, $bot_name) {
    $data = array(
      'user_id' => $user_id,
      'name' => $bot_name,
      'language' => 'C++'
    );
    $this->db->insert($this->table_name, $data);
  }
}

?>
