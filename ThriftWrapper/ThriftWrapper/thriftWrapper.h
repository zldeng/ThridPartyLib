/*
* Copyright (C) 2018 All rights reserved.
* file : thriftWrapper.h
* author : zldeng hitdzl@gmail.com
* date : 2018-08-09
* description : enjoy coding!
*/

#ifndef _THRIFTWRAPPER_H_
#define _THRIFTWRAPPER_H_
#include <iostream>
#include <string>
#include <utility>
#include "Common/ThirdParty/boost/boost/shared_ptr.hpp"
#include "Common/ThirdParty/thrift/include/protocol/TBinaryProtocol.h"
#include "Common/ThirdParty/thrift/include/protocol/TDebugProtocol.h"
#include "Common/ThirdParty/thrift/include/protocol/TJSONProtocol.h"
#include "Common/ThirdParty/thrift/include/transport/TBufferTransports.h"
#include "Common/ThirdParty/thrift/include/transport/TSocket.h"
#include "Common/ThirdParty/thrift/include/server/TNonblockingServer.h"
#include "Common/ThirdParty/thrift/include/concurrency/PosixThreadFactory.h"
#include "Common/ThirdParty/thrift/include/concurrency/ThreadManager.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

namespace ThriftWrapper
{
	template <typename HandlerT, typename ProcessorT>
	class ThriftNonBlockServer
	{
		private:
			int port_;
			boost::shared_ptr<TNonblockingServer> server_;
			boost::shared_ptr<HandlerT> handler_;
			boost::shared_ptr<ProcessorT> processor_;

			ThriftNonBlockServer(const ThriftNonBlockServer&) = delete;
			ThriftNonBlockServer& operator=(const ThriftNonBlockServer&) = delete;

		public:

			ThriftNonBlockServer(const int port,
					boost::shared_ptr<HandlerT> handler):port_(port),
				handler_(handler){
			}

			~ThriftNonBlockServer(){}
			
			void Start()
			{
				if(handler_.get() == nullptr)
				{
					handler_.reset(new HandlerT());
				}

				processor_.reset(new ProcessorT(handler_));

				server_.reset(new TNonblockingServer(processor_,port_));
				server_->serve();
			}
	};

	template <typename HandlerT,typename ProcessorT>
	class ThriftNonBlockingServerMutiThread
	{
		private:
			int port_;
			int thread_num_;

			shared_ptr<TNonblockingServer> server_;
			shared_ptr<HandlerT> handler_;
			shared_ptr<ProcessorT> processor_;
			shared_ptr<TProtocolFactory> proto_factory_;
			shared_ptr<apache::thrift::concurrency::ThreadManager> thread_manager_;

			ThriftNonBlockingServerMutiThread(const ThriftNonBlockingServerMutiThread&) = delete;
			ThriftNonBlockingServerMutiThread& operator=(const ThriftNonBlockingServerMutiThread&) = delete;


		public:
			ThriftNonBlockingServerMutiThread(const int port,
					boost::shared_ptr<HandlerT> handler,
					const int thread_num):port_(port),
				thread_num_(thread_num),
				handler_(handler){
			}
			~ThriftNonBlockingServerMutiThread(){}	
			void Start()
			{
				if (handler_.get() == nullptr)
				{
					std::cerr << "handler is null";
					return;
				}
			
				processor_.reset(new ProcessorT(handler_));
				proto_factory_.reset(new TBinaryProtocolFactory());
			
				thread_manager_ = apache::thrift::concurrency::ThreadManager::newSimpleThreadManager(thread_num_);
			
				boost::shared_ptr<apache::thrift::concurrency::PosixThreadFactory> thread_factory;
				thread_factory.reset(new apache::thrift::concurrency::PosixThreadFactory());
				thread_manager_->threadFactory(thread_factory);
				thread_manager_->start();
			
				server_.reset(new TNonblockingServer(processor_,
							proto_factory_,
							port_,
							thread_manager_));
			
				server_->serve();
			}
	};

	template<typename Client>
	class ThriftClient
	{
		private:
			std::string host_;
			int port_;

			bool connected_;
			std::string transport_class_ = "TFramedTransport"; // if server is non-blocking server, TFramedTransport is required

			static const int kConnectionTimeout = 500;
			static const int kReceiveTimeout = 10000;
			static const int kSendTimeout = 10000;
			static const int kFrameSize = 128 * 1024;
			int connection_timeout_;
			int receive_timeout_;
			int send_timeout_;

			shared_ptr<TSocket> socket_;
			shared_ptr<TTransport> transport_;
			shared_ptr<TProtocol> protocol_;
			shared_ptr<Client> client_;

			ThriftClient(const ThriftClient&) = delete;
			ThriftClient& operator=(const ThriftClient&) = delete;

			void ConnectIfNecessary()
			{
				if(connected_)
					return;
			
				socket_.reset(new TSocket(host_,port_));
				socket_->setConnTimeout(connection_timeout_);
				socket_->setRecvTimeout(receive_timeout_);
				socket_->setSendTimeout(send_timeout_);
			
				if (transport_class_ == "TFramedTransport")
				{
					transport_.reset(new TFramedTransport(socket_,kFrameSize));
				}
				else if ("TBufferedTransport" == transport_class_)
				{
					transport_.reset(new TBufferedTransport(socket_,kFrameSize));
				}
				else
				{
					std::cerr << "Unsupported transport : " << transport_class_ << ". Use TFramedTransport as default\n";
			
					transport_.reset(new TFramedTransport(socket_,kFrameSize));
				}
			
				try
				{
					transport_->open();
				}
				catch(...)
				{
					std::cerr << "failed to connect  to " << host_ << ":" << port_;
					return; 
				}
			
				protocol_.reset(new TBinaryProtocol(transport_));
				client_.reset(new Client(protocol_));
				connected_ = true;
			}
		public:
			ThriftClient(const std::string & host,
					const int port):host_(host),port_(port),connected_(false){
				connection_timeout_ = kConnectionTimeout;
				receive_timeout_ = kReceiveTimeout;
				send_timeout_ = kSendTimeout;
			}

			void SetConnectionTimeout(const int timeout)
			{
				connection_timeout_ = timeout;
			}

			void SetReceiveTimeout(const int timeout)
			{
				receive_timeout_ = timeout;
			}

			void SetSendTimeout(const int timeout)
			{
				send_timeout_ = timeout;
			}


			virtual ~ThriftClient(){}

			Client* Connecte()
			{
				ConnectIfNecessary();
				return client_.get();
			}

			Client* GetDuplicateClient()
			{
				boost::shared_ptr<TProtocol> protocol(static_cast<TBinaryProtocol*>(nullptr));
				boost::shared_ptr<Client> client(static_cast<Client*>(nullptr));
				boost::shared_ptr<TSocket> socket(new TSocket(host_,port_));
				socket->setConnTimeout(connection_timeout_);
				socket->setRecvTimeout(receive_timeout_);
				socket->setSendTimeout(send_timeout_);
			
				boost::shared_ptr<TTransport> transport(new TFramedTransport(socket,kFrameSize));
			
				try
				{
					transport->open();
				}
				catch(...)
				{
					std::cerr << "fail to connet to " << host_ << ":" << port_ << std::endl;
					return NULL;
				}
			
				protocol.reset(new TBinaryProtocol(transport));
				client.reset(new Client(protocol));
			
				return client.get();
			}

			void CallServiceFail()
			{
				connected_ = false;
			}

			shared_ptr<TTransport> GetTransport()
			{
				return transport_;
			}
	};
}


#endif
