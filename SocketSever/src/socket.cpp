#include "../include/socket.h"
#include "iostream"

Socket::Socket():iaddrSize(sizeof(SOCKADDR_IN))
{
}

bool Socket::SocketInit()
{
	WSAStartup(0x0202, &wsaData);
	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);
	local.sin_addr.S_un.S_addr = inet_addr("192.168.179.1");
	if (connect(sListen, (sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
	{  //¡¨Ω” ß∞‹ 
		printf("connect error !");
		closesocket(sListen);
		return false;
	}
	return true;
}

bool Socket::SocketRecv(SOCKET s, char* buf, int len, int flag)
{
	ret = recv(s, buf, len, flag);
	if (ret < 0)
	{
		std::cout << ret << std::endl;
		return false;
	}
	else if(ret ==0)
		return false;
	else return true;
}

bool Socket::SocketClose(SOCKET s)
{
	closesocket(s);
	return false;
}
