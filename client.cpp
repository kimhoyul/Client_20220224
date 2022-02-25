#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;


int main()
{
	//1. 윈속 초기화, DLL 로딩
	WSAData WsaData;

	if (WSAStartup(MAKEWORD(2, 2), &WsaData))
	{
		cout << "Winsock Error : " << GetLastError() << endl;
		exit(-1);
	}

	//2. 소켓 생성
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	//3. 주소세팅
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_port = htons(5001); //host to network short
	ServerAddr.sin_family = PF_INET; //IP V4
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		//4. 연결 - 물리적인 연결을 Socket랑 연결
	if (connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "connect Error : " << GetLastError() << endl;
		exit(-1);
	}

	cout << "연결성공" << endl;

	char Buffer[] = "give me message.";
	send(ServerSocket, Buffer, strlen(Buffer) + 1, 0);
	
	cout << "send message : " << Buffer << endl;

	char Result[1024];
	recv(ServerSocket, Result, 1024, 0);

	cout << "Server Sended : " << Result << endl;

	//6. 소켓 닫기
	closesocket(ServerSocket);

	//7. 윈속 정리
	WSACleanup();

	return 0;
}