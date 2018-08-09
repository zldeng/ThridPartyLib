thrift_library(
	name = 'structThrift',
	srcs = ['struct.thrift']
)


thrift_library(
	name = 'serviceThrift',
	srcs = ['service.thrift'],
	deps = ['//ThriftWrapper/Proto:structThrift']
)
