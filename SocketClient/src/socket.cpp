#include "../include/socket.h"
#include "iostream"

Socket::Socket()
{
}

bool Socket::SocketInit()
{
	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// �����ͻ����׽���      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/IPЭ���壻      
														 //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��      
	// ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�IP��ַ��)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0      
	server.sin_family = PF_INET; //������ַ��ʽ��TCP/IP��ַ��ʽ      
	server.sin_port = htons(PORT); //ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order      
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //ָ�����ӷ�������IP��ַ      
														//�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���IP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���IP��ַ      
														//inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��ΪIP��ַ��ʽ      
	if (bind(sClient, (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//��ʼ����  
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