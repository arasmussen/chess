<?php

require_once(getenv('THRIFT_PHP_DIR').'/Thrift.php');
require_once(getenv('THRIFT_PHP_DIR').'/protocol/TBinaryProtocol.php');
require_once(getenv('THRIFT_PHP_DIR').'/transport/TSocket.php');
require_once(getenv('THRIFT_PHP_DIR').'/transport/THttpClient.php');
require_once(getenv('THRIFT_PHP_DIR').'/transport/TBufferedTransport.php');

$GEN_DIR = getenv('CHESS_ROOT').'/thrift/gen-php';
require_once($GEN_DIR.'/ChessGameServer.php');
require_once($GEN_DIR.'/ChessGameServer_types.php');

class ChessGameServer {
  private $socket;
  private $transport;
  private $protocol;
  private $client;

  public function __construct() {
    try {
      $this->socket = new TSocket('localhost', 9090);
      $this->transport = new TBufferedTransport($this->socket, 1024, 1024);
      $this->protocol = new TBinaryProtocol($this->transport);
      $this->client = new ChessGameServerClient($this->protocol);

      $this->transport->open();
    } catch (TException $tx) {
      print 'TException: '.$tx->getMessage()."\n";
    }
  }

  public function __destruct() {
    $this->transport->close();
  }

  public function startGame($whiteAlgorithm, $blackAlgorithm) {
    $this->client->startGame($whiteAlgorithm, $blackAlgorithm);
  }
}


// ---------------- TESTING ----------------------

$chessGameServer = new ChessGameServer;
$chessGameServer->startGame($argv[1], $argv[2]);

?>
