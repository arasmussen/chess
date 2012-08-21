#include "ChessGameServer.h"
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>

#include "ChessGameManager.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class ChessGameServerHandler : virtual public ChessGameServerIf {
 public:
  ChessGameServerHandler() : 
		manager(new ChessGameManager())
	{}

	~ChessGameServerHandler() {
		delete manager;
	}

  void startgame(const std::string& whiteAlgorithm, const std::string& blackAlgorithm) {
		manager->startGame(whiteAlgorithm.c_str(), blackAlgorithm.c_str());
  }

	private:
		ChessGameManager *manager;
};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ChessGameServerHandler> handler(new ChessGameServerHandler());
  shared_ptr<TProcessor> processor(new ChessGameServerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

