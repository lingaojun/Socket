#ifndef __SOCKET_H
#define __SOCKET_H

#define SERVER_ADDRESS "192.168.179.1" //��������IP��ַ      
#define PORT           5150         //�������Ķ˿ں�    
#include <WINSOCK2.H>   
class Socket
{
public:
	WSADATA wsaData;
	//���������׽���      
	SOCKET sClient;
	SOCKET sListen;
	//����Զ�̷������ĵ�ַ��Ϣ      
	SOCKADDR_IN server;
	//�ɹ������ֽڵĸ���      
	int ret;
	Socket();
	bool SocketInit();
	bool SocketSend(SOCKET s,char *buf,int len,int flags);
};
#endif // !__SOCKET_H
