#ifndef __SOCKET_H
#define __SOCKET_H

#define SERVER_ADDRESS "192.168.179.1" //服务器端IP地址      
#define PORT           5150         //服务器的端口号    
#include <WINSOCK2.H>   
class Socket
{
public:
	WSADATA wsaData;
	//连接所用套节字      
	SOCKET sClient;
	SOCKET sListen;
	//保存远程服务器的地址信息      
	SOCKADDR_IN server;
	//成功接收字节的个数      
	int ret;
	Socket();
	bool SocketInit();
	bool SocketSend(SOCKET s,char *buf,int len,int flags);
};
#endif // !__SOCKET_H
