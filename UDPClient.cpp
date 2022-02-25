#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSAData wsaData;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET ServerSocket;
    ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);

    SOCKADDR_IN ServerAddr;
    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = PF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ServerAddr.sin_port = htons(50000);
    int SeverAddrSize = sizeof(ServerAddr);

    char Message[] = "Hello World";
    sendto(ServerSocket, Message, strlen(Message) + 1, 0, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

    char Buffer[1024] = { 0, };
    int ReceiveLength = recvfrom(ServerSocket, Buffer, 1023, 0, (SOCKADDR*)&ServerAddr, &SeverAddrSize);

    cout << Buffer << endl;


}