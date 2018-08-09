// Client.cpp : 定义控制台应用程序的入口点。
//
 
#include <iostream>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "thrift_test/Proto/GetPerson.h"
 

#include "ThriftWrapper/ThriftWrapper/thriftWrapper.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
 
using boost::shared_ptr;
using namespace std;

/*
int main(int argc, char* argv[])
{
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 19110));
	//boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));

	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket,1024*128));
 
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	GetPersonClient client(protocol);
 
	try
	{
		//设置发送、接收、连接超时
		socket->setConnTimeout(5000);
		socket->setRecvTimeout(5000);
		socket->setSendTimeout(5000);
 
		transport->open();
 
		//insert your code here
		Person person;
		person.__set_name("dzl");
		person.__set_age(20);
		person.__set_male(true);

		ResPerson res;
		client.getPersonInfo(res,person);
		
		cout << res.new_name << "\t" << res.male << endl;
		transport->close();
 
		printf("send success!\n");
	}
	catch (...)
	{
	}
 
	return 0;
}
*/


int main()
{
	const string server_host = "127.0.0.1";
	const int server_port = 19110;
	boost::shared_ptr<ThriftWrapper::ThriftClient<GetPersonClient> > thrift_client(new ThriftWrapper::ThriftClient<GetPersonClient>(server_host,server_port));

	auto client = thrift_client->Connecte();
	
	Person person;
	person.__set_name("dzl");
	person.__set_age(20);
	person.__set_male(true);

	ResPerson res;
	client->getPersonInfo(res,person);
	
	cerr << res.new_name << "\t" << res.male << endl;


}
