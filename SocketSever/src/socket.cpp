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
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sListen, (struct sockaddr *) &local, sizeof(SOCKADDR_IN));

	listen(sListen, 1);

	sClient = accept(sListen, (struct sockaddr *) &client, &iaddrSize);
	return true;
}

bool Socket::SocketRecv(SOCKET s, char* buf, int len, int flag)
{
	bool rs = true;
	while (rs)
	{
		ret = recv(s, buf, len, 0); 
		if (ret < 0)
		{
			// 由于是非阻塞的模式,所以当buflen为EAGAIN时,表示当前缓冲区已无数据可读
			// 在这里就当作是该次事件已处理
			if (ret == EAGAIN)
				break;
			else
				return false;
		}
		else if (ret == 0)
		{
			// 这里表示对端的socket已正常关闭.
			return true;
		}
		if (ret != sizeof(buf))
			rs = 0;
		else
			rs = 1;// 需要再次读取
	}
	return true;


}

bool Socket::SocketClose(SOCKET s)
{
	closesocket(s);
	return false;
}
