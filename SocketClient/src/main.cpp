#include <WINSOCK2.H> 
#include "windows.h"
#include <stdio.h>   
#include <iostream>
#include "../include/socket.h"
#include "fstream"
#include "thread"
#pragma comment(lib, "ws2_32.lib")      

void thread1()
{
	Socket SocketClient;
	SocketClient.SocketInit();

	char buffer[1024];
	std::ifstream ifs;
	ifs.open("../../../test.txt");
	if (!ifs.is_open())
	{
		std::cout << "Cant Open The File" << std::endl;
	}
	while (!ifs.eof())
	{
		ifs.getline(buffer, 1024);
		//std::cout << buffer << std::endl;
	}
	printf("Send:");
	strcpy(SocketClient.szMessage, buffer);
	ifs.close();
	std::cout << SocketClient.szMessage << std::endl;
	std::cout << strlen(SocketClient.szMessage) << std::endl;
	if (SocketClient.SocketSend(SocketClient.sClient, SocketClient.szMessage, strlen(SocketClient.szMessage), 0) == false) //sClient指明用哪个连接发送； szMessage指明待发送数据的保存地址 ；strlen(szMessage)指明数据长度    
	{
		std::cout << "SocketSend Error " << std::endl;
	}
	// 释放连接和进行结束工作      
	closesocket(SocketClient.sClient);
	WSACleanup();

}
void thread2()
{

}

int main()
{
	std::thread t1(thread1);
	std::thread t2(thread2);
	t1.join();
	t2.join();
	while (1)
	{
		Sleep(1000); //延时1S
	} 
	return 0;		
}