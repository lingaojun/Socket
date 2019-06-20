#include <WINSOCK2.H> 
#include "windows.h"
#include <stdio.h>   
#include <iostream>
#include "../include/socket.h"
#include "fstream"
#include "thread"
#include "io.h"
#pragma comment(lib, "ws2_32.lib")      

//Sever端 发送文件数据
constexpr auto BUFFSIZE = 1024;

void thread1()
{
	Socket SocketClient;
	SocketClient.SocketInit();  
	std::string srcFileName = "../../../test.txt";
	std::ifstream srcFile;
	srcFile.open(srcFileName.c_str(), std::ios::binary);
	if (!srcFile) 
	{
		return;
	}
	int nAddrlen = sizeof(SocketClient.server);
	while (1)
	{
		printf("等待连接...\n");
		SocketClient.sListen = accept(SocketClient.sClient, (SOCKADDR *)&SocketClient.server, &nAddrlen);
		if (SocketClient.sListen == INVALID_SOCKET)
		{
			printf("accept error !");
			continue;
		}
		printf("接受到一个连接：%s \r\n", inet_ntoa(SocketClient.server.sin_addr));
		int haveSend = 0;
		long long int filesize = 0;
		char buffer[BUFFSIZE] = { 0 };
		int readLen = 0;
		std::string srcFileName = "../../../test.txt";
		std::ifstream srcFile;
		srcFile.open(srcFileName.c_str(), std::ios::binary);
		if (!srcFile) 
		{
			std::cout << "srcFile is error " << std::endl;
		}
		srcFile.seekg(0, std::ios::end);
		filesize = srcFile.tellg();
		srcFile.seekg(0, std::ios::beg);
		while (!srcFile.eof()) 
		{
			srcFile.read(buffer, BUFFSIZE);//read之后文件指针会自动移动
			readLen = srcFile.gcount();
			send(SocketClient.sListen, buffer, readLen, 0);
			haveSend += readLen;
			std::cout << haveSend << "B/" << filesize << "B"<<std::endl;
		}
		srcFile.close();
		std::cout << "send: " << haveSend << "B" << std::endl;

		closesocket(SocketClient.sListen);
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
	//std::thread t2(thread2);
	t1.join();
	//t2.join();
	while (1)
	{
		Sleep(1000); //延时1S
	} 
	return 0;		
}