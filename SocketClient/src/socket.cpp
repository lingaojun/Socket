#include "../include/socket.h"
#include "iostream"

Socket::Socket()
{
}

bool Socket::SocketInit()
{
	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// 创建客户端套节字      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/IP协议族；      
														 //SOCK_STREAM, IPPROTO_TCP具体指明使用TCP协议      
	// 指明远程服务器的地址信息(端口号、IP地址等)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //先将保存地址的server置为全0      
	server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式      
	server.sin_port = htons(PORT); //指明连接服务器的端口号，htons()用于 converts values between the host and network byte order      
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //指明连接服务器的IP地址      
														//结构SOCKADDR_IN的sin_addr字段用于保存IP地址，sin_addr字段也是一个结构体，sin_addr.s_addr用于最终保存IP地址      
														//inet_addr()用于将 形如的"127.0.0.1"字符串转换为IP地址格式      
	if (bind(sClient, (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听  
	if (listen(sClient, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return false;
	}
	return true;
}

bool Socket::SocketSend(SOCKET s, char *buf, int len, int flags)
{
	int ret = send(s, buf, len, flags);
	if (ret < 0)
	{
		std::cout << "send is error" << std::endl;
		return false;
	}
	return true;
}