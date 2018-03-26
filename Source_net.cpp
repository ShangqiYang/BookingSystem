#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
 

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

void Client();
void Server();

int __cdecl main(int argc, char **argv)
{
	int isclient;
	scanf_s("%d", &isclient);
	if (isclient == 1)
	{
		cout << "Client mode" << endl;
		Client();
	}
	else
	{
		cout << "Server mode" << endl;
		Server();
	}
	system("pause");
	return 0;
}

void Client()
{
	char send_buffer[60];
	char recv_buffer[60];
	char ip[60];
	scanf_s("%s", ip,_countof(ip));
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		break;
	}

	freeaddrinfo(result);
	// Send login credencials
	recv_buffer[0] = 'n';
	while (recv_buffer[0] == 'n')
	{
		int studentID = 0;
		string password = "";
		cout << "Stevens ID:";
		cin >> studentID;
		cout << "Password:";
		cin >> password;
		_itoa_s(studentID, send_buffer, 10);
		send(ConnectSocket, send_buffer, (int)strlen(send_buffer) + 1, 0);
		send(ConnectSocket, password.c_str(), (int)strlen(password.c_str()) + 1, 0);

		// Receive until the peer closes the connection
		iResult = recv(ConnectSocket, recv_buffer, 60, 0);
		if (recv_buffer[0] == 'n')
		{
			cout << "Wrong passowrd or username" << endl;
		}
		else if (recv_buffer[0] == 's')
		{
			cout << "Successful logined as student" << endl;
		}
		else if (recv_buffer[0] == 't')
		{
			cout << "Successful logined as administrator" << endl;
		}
	}
	// cleanup
	iResult = shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	WSACleanup();

}

void Server()
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);

	while (true)
	{
		int studentID = 0;
		string password = "";
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);

		// Receive until the peer shuts down the connection
		bool match = false;
		while (!match)
		{
			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			cout << recvbuf << endl;
			studentID = atoi(recvbuf);
			iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			password = string(recvbuf);
			cout << password << endl;
			ifstream login("login.txt");
			int it_ID;
			string it_PW;
			int identity;
			while (!login.eof())    //reach the end of file
			{
				login >> it_ID >> it_PW >> identity;
				if (it_ID == studentID && it_PW == password)
				{
					match = true;
					break;
				}
			}
			login.close();
			if (!match)
			{
				iSendResult = send(ClientSocket, "n", 2, 0);
				cout << "Client login attempt failed" << endl;
			}
			else
			{
				cout << "Client have successfully logined as "; 
				if (identity == 0)
				{
					iSendResult = send(ClientSocket, "t", 2, 0);
					cout << "administrator." << endl;
				}
				else
				{
					iSendResult = send(ClientSocket, "s", 2, 0);
					cout << "student." << endl;
				}
			}
		}
		
		
		

		// shutdown the connection since we're done
		iResult = shutdown(ClientSocket, SD_SEND);
	}


	// cleanup
	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();
}
