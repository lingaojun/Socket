// socket1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <WINSOCK2.H>   
#include <stdio.h>     
#include "../include/socket.h"  

#pragma comment(lib, "ws2_32.lib")      

int main()
{
	Socket SocketSever;
	printf("Accepted client:%s:%d\n", inet_ntoa(SocketSever.client.sin_addr),ntohs(SocketSever.client.sin_port));
	SocketSever.SocketInit();
	while (TRUE) 
	{
		SocketSever.SocketRecv(SocketSever.sClient, SocketSever.szMessage, MSGSIZE, 0);
		SocketSever.szMessage[SocketSever.ret] = '\0';
		printf("Received [%d bytes]: '%s'\n", SocketSever.ret, SocketSever.szMessage);
	}
	return 0;
}


