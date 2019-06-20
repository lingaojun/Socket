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
	{  //����ʧ�� 
		printf("connect error !");
		closesocket(sListen);
		return false;
	}
	return true;
}

bool Socket::SocketRecv(SOCKET s, char* buf, int len, int flag)
{
	bool rs = true;
	while (true)
	{
		ret = recv(s, buf, len, flag);
		std::cout << ret << std::endl;
		if (ret < 0)
		{
			// �����Ƿ�������ģʽ,���Ե�buflenΪEAGAINʱ,��ʾ��ǰ�������������ݿɶ�
			// ������͵����Ǹô��¼��Ѵ���
			if (ret == EAGAIN)
				break;
			else
				return false;
		}
		else if (ret == 0)
		{
			// �����ʾ�Զ˵�socket�������ر�.
			//std::cout << "Socket Recv is over" << std::endl;
			break;
		}
		if (ret != sizeof(buf))
			rs = 0;
		else
			rs = 1;// ��Ҫ�ٴζ�ȡ
	}
	return true;


}

bool Socket::SocketClose(SOCKET s)
{
	closesocket(s);
	return false;
}
