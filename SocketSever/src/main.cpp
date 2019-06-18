// socket1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <WINSOCK2.H> 
#include "windows.h"
#include <stdio.h>    
#include "iostream"
#include "../include/socket.h"  
#include "fstream"
#include "thread"
#pragma comment(lib, "ws2_32.lib")      

void thread1()
{
	Socket SocketSever;
	bool SocketRecvStop = false;
	printf("Accepted client:%s:%d\n", inet_ntoa(SocketSever.client.sin_addr), ntohs(SocketSever.client.sin_port));
	SocketSever.SocketInit(); //SocketInit
	if (!SocketSever.SocketRecv(SocketSever.sClient, SocketSever.szMessage, MSGSIZE, 0)) //Recv
	{
		std::cout << "SocketRecv Failed" << std::endl;
		SocketSever.SocketClose(SocketSever.sListen);
	}
	SocketSever.szMessage[SocketSever.ret] = '\0';
	printf("Received [%d bytes]: '%s'\n", SocketSever.ret, SocketSever.szMessage);
}

void thread2(int a)
{
	
}
int main()
{
	int a;
	std::thread t1(thread1);
	std::thread t2(thread2,a);
	t1.join();
	while (1)
	{
		Sleep(1000);
	}
	return 0;
}


