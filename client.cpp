#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main()
{
	//1. ���� �ʱ�ȭ, DLL �ε�
	WSAData WsaData;

	if (WSAStartup(MAKEWORD(2, 2), &WsaData))
	{
		cout << "Winsock Error : " << GetLastError() << endl;
		exit(-1);
	}

	//2. ���� ����
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	//3. �ּҼ���
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_port = htons(5001); //host to network short
	ServerAddr.sin_family = PF_INET; //IP V4
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		//4. ���� - �������� ������ Socket�� ����
	if (connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "connect Error : " << GetLastError() << endl;
		exit(-1);
	}

	cout << "���Ἲ��" << endl;

	char Buffer[] = "give me message.";
	send(ServerSocket, Buffer, strlen(Buffer) + 1, 0);
	
	cout << "send message : " << Buffer << endl;

	char Result[1024];
	recv(ServerSocket, Result, 1024, 0);

	cout << "Server Sended : " << Result << endl;

	//6. ���� �ݱ�
	closesocket(ServerSocket);

	//7. ���� ����
	WSACleanup();

	return 0;
}