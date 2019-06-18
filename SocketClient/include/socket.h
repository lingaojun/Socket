#ifndef __SOCKET_H
#define __SOCKET_H

#define SERVER_ADDRESS "192.168.1.105" //��������IP��ַ      
#define PORT           5150         //�������Ķ˿ں�      
#define MSGSIZE        1024        //�շ��������Ĵ�С

#include <WINSOCK2.H>   
class Socket
{
public:
	WSADATA wsaData;
	//���������׽���      
	SOCKET sClient;
	//����Զ�̷������ĵ�ַ��Ϣ      
	SOCKADDR_IN server;
	//�շ�������      
	char szMessage[MSGSIZE];
	//�ɹ������ֽڵĸ���      
	int ret;
	Socket();
	bool SocketInit();
	bool SocketSend(SOCKET s,char *buf,int len,int flags);
};
#endif // !__SOCKET_H
