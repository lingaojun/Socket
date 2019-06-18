#include <WINSOCK2.H>   
#include <stdio.h>   
#include <iostream>
#include "../include/socket.h"
    
#pragma comment(lib, "ws2_32.lib")      

int main()
{
	Socket SocketClient;
	SocketClient.SocketInit();
	while (TRUE) 
	{
		printf("Send:");    
		std::cin >> SocketClient.szMessage;
		SocketClient.SocketSend(SocketClient.sClient, SocketClient.szMessage, strlen(SocketClient.szMessage), 0); //sClient指明用哪个连接发送； szMessage指明待发送数据的保存地址 ；strlen(szMessage)指明数据长度      
	}

	// 释放连接和进行结束工作      
	closesocket(SocketClient.sClient);
	WSACleanup();
	return 0;
}