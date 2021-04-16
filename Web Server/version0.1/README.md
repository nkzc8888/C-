这一版大约花费了3天的时间，主要花在对一些基础概念的入门学习上。这个版本实现了最简单的通讯，由于过于简单就只写了一个main函数。 
总结一下Server： 
1.对可能到来的Client请求创建套接字socket（包含协议（IPv4: AF_INIT/ IPv6: AF_INIT6）、端口、类型（TCP: SOCK_STREAM/ UDP: SOCK_DGRAM）） 
2.等待Client发送连接请求，并进行连接（accept） 
3.读Client的请求（read/recv） 
4.响应Client的请求，发送给Client请求的数据（write/send） 
5.关闭连接（close） 
Clinet： 
1.创建套接字client_fd+client_addr+bind 
2.创建server_addr保存服务器的信息，用以connect 
3.用send和recv与服务器通讯 
