#ifndef __SOCKET_H
#define __SOCKET_H

#include <WINSOCK2.H>   
constexpr auto PORT = 5150;
constexpr auto MSGSIZE = 1024;

class Socket
{
public:
	WSADATA wsaData;
	SOCKET sListen;
	SOCKET sClient;
	SOCKADDR_IN local;
	SOCKADDR_IN client;
	char szMessage[MSGSIZE];
	int ret;
	int iaddrSize;
	Socket();
	bool SocketInit();
	bool SocketRecv(SOCKET s,char* buf,int len, int flag);
	bool SocketClose(SOCKET s);
private:

};
#endif // !__SOCKET_H
