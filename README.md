# ThridPartyLib
有用的第三方C++库

- glog
1. git地址：https://github.com/google/glog
2. install：

```
sh autogen.sh && ./configure && make && make install
```

3. 使用demo：main.cpp，demo中编译时用blade
4. blade链接:https://github.com/chen3feng/typhoon-blade

# threadPool
使用C++11实现的简单的线程池

# ThriftWrapper
- 基于C++模板实现的对thrift server、client的封装，方便快速实现基于thrift的服务端和客户端
- thrift参考资料：
1. [Thrift: Scalable Cross-Language Services Implementation](http://thrift.apache.org/static/files/thrift-20070401.pdf) 
2. [Apache Thrift](http://jnb.ociweb.com/jnb/jnbJun2009.html)
3. [Thrift server端的几种工作模式分析](https://blog.csdn.net/houjixin/article/details/42779915)

# gflags_demo
google gflags命令行参数处理库，参考链接：https://github.com/gflags/gflags
