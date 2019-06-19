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
	int blocknums;
	std::cout << "RecvFun" << std::endl;
	std::ofstream ofs("../../../out.txt");
	bool SocketRecvStop = false;
	printf("Accepted client:%s:%d\n", inet_ntoa(SocketSever.client.sin_addr), ntohs(SocketSever.client.sin_port));
	SocketSever.SocketInit(); //SocketInit
	SocketSever.ret = SocketSever.SocketRecv(SocketSever.sClient, SocketSever.szMessage, MSGSIZE, 0); //先接受blocknum
	blocknums = atoi(SocketSever.szMessage);
	printf("FileBuffBlockNum is %d", blocknums);
	for (int i = 0; i < blocknums; i++)
	{
		std::cout << i << std::endl;
			SocketSever.SocketRecv(SocketSever.sClient, SocketSever.szMessage, MSGSIZE, 0);
		std::cout << SocketSever.szMessage << std::endl;
	}
	ofs << SocketSever.szMessage; //将读取来得内容流入需要输出的文档。
	ofs.close();
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


