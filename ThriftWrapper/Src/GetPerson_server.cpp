// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "thrift_test/Proto/GetPerson.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <string>
#include <iostream>

#include "ThriftWrapper/ThriftWrapper/thriftWrapper.h"

using namespace std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class GetPersonHandler : virtual public GetPersonIf {
 public:
  GetPersonHandler() {
    // Your initialization goes here
  }

  void getPersonInfo( ::ResPerson& _return, const  ::Person& person) {
    // Your implementation goes here
	
	const string person_name = person.name;
	//const int32_t person_age = person.age;
	const bool is_male = person.male;

	_return.__set_new_name(person_name + "_new");
	_return.__set_male(!is_male);
	
	std::cout << "getPersonInfo done";
  }

};

/*
int main(int argc, char **argv) {
  int port = 19110;
  shared_ptr<GetPersonHandler> handler(new GetPersonHandler());
  shared_ptr<TProcessor> processor(new GetPersonProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
*/


int main()
{
	int port = 19110;
	boost::shared_ptr<GetPersonHandler> handler(new GetPersonHandler());//(new GetPersonHandler());
	//ThriftWrapper::ThriftNonBlockServer<GetPersonHandler,GetPersonProcessor> server(port,handler);
	
	ThriftWrapper::ThriftNonBlockingServerMutiThread<GetPersonHandler,GetPersonProcessor> server(port,handler,5);
	server.Start();

}
