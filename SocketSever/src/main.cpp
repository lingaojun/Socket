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

constexpr auto BUFFSIZE = 1024;

void thread1()
{
	Socket SocketSever;
	char buffer[BUFFSIZE] = { 0 };
	int readLen = 0;
	long long int filesize = 0;
	std::string desFileName = "../../../out.txt";
	std::ofstream desFile;
	std::cout << "start recv!" << std::endl;
	desFile.open(desFileName.c_str(), std::ios::binary);
	if (!desFile)
	{
		std::cout << "desFile is Null "<< std::endl;
	}

	SocketSever.SocketInit();
	do
	{
		if (SocketSever.SocketRecv(SocketSever.sListen, buffer, BUFFSIZE, 0))
		{
			std::cout << "filesize is " << filesize << std::endl;
			std::cout << buffer << std::endl;
			desFile.write(buffer, SocketSever.ret);
			filesize += SocketSever.ret;
		}
		else
		{
			std::cout << "SocketRecv failed" << std::endl;
			break;
		}
	} while (true);

	desFile.close();
	
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


