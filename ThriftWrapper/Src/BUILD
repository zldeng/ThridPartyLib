cc_binary(name = 'personServer',
	srcs = [
		'GetPerson_server.cpp',
	],
	deps = [
		'//ThriftWrapper/Proto:serviceThrift',
		'//Common/ThirdParty/thrift-1.0.0-dev:thriftnb',
		'//Common/ThirdParty/thrift-1.0.0-dev:thrift',
		'//Common/ThirdParty/libevent-2.0.11-stable:event'

	],
	extra_cppflags = ['-lpthread', '-lboost_thread-mt', '-lboost_system'],
	optimize = ['-std=c++11']
)

cc_binary(name = 'personClient',
	srcs = [
		'GetPerson_client.cpp',
	],
	deps = [
		'//ThriftWrapper/Proto:serviceThrift',
		'//Common/ThirdParty/thrift-1.0.0-dev:thriftnb',
		'//Common/ThirdParty/thrift-1.0.0-dev:thrift',
		'//Common/ThirdParty/libevent-2.0.11-stable:event'
	],	
	optimize = ['-std=c++11']
)
