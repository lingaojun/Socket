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
void thread1()
{
	Socket SocketClient;
	SocketClient.SocketInit();
	char buffer[1024];
	char *firstblock = new char ;
	std::ifstream ifs;
	int filesize = 0;
	int blocknums = 0;
	int readLen = 0;
	ifs.open("../../../test.txt",std::ios::in|std::ios::binary);
	std::cout << "SendFun" << std::endl;
	if (!ifs.is_open())
	{
		std::cout << "Cant Open The File" << std::endl;
	}
	else
	{
		ifs.seekg(0, std::ios::end); //对文件进行定位到最后
		filesize = ifs.tellg(); //因为定位到文件结束，所以为文件大小
		ifs.seekg(0, std::ios::beg);//再次定位到文件开头
		std::cout << "size is "<< filesize << std::endl;
	}
	blocknums = (filesize % (MSGSIZE-1)) ? ( filesize / (MSGSIZE-1)+ 1) : (filesize / (MSGSIZE-1));
	std::cout << "blocknums is " << blocknums << std::endl;
	itoa(blocknums, firstblock, 10);
	SocketClient.SocketSend(SocketClient.sClient, firstblock, strlen(SocketClient.szMessage), 0); //先发送block数量
	for (int i = 0; i < blocknums; i++)
	{
		ifs.read(SocketClient.szMessage, MSGSIZE-1);
		SocketClient.szMessage[MSGSIZE-1] = '\0';
		SocketClient.SocketSend(SocketClient.sClient, SocketClient.szMessage, strlen(SocketClient.szMessage), 0);
		std::cout << SocketClient.szMessage << std::endl;
	}

	// 释放连接和进行结束工作      
	closesocket(SocketClient.sClient);
	WSACleanup();

}
void thread2()
{
	Socket SocketClient;
	SocketClient.SocketInit();

	char buffer[1024];
	std::ifstream ifs;
	ifs.open("../../../test.png");
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