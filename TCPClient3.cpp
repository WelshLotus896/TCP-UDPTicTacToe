#include "stdafx.h"
#include "TCPClient3.h"


TCPClient3::TCPClient3()
{

}


TCPClient3::~TCPClient3()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is for connecting to the server or in this case, starting the process of connecting to one
////////////////////////////////////////////////////////////////////////////////////////////////////
int TCPClient3::connectServer(TCHAR* serverName) //change this to include server name
{
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0)
	{

		printf("WSA Start up failed: %d\n", iResult);
		return 1;
	}

	establishConnection(serverName);

}


////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is for establishing the connection between the client and the server
////////////////////////////////////////////////////////////////////////////////////////////////////
int TCPClient3::establishConnection(TCHAR* serverName)
{
	printf("Please Enter your Username: \n");
	cin >> sendbuf;


	//Commence While Loop to check for keyboard stroke input
	
		system("CLS");
		printf("*************************************************************************************************************\n");
		printf("*************************************** Welcome to Hardhugadr 1.0 *******************************************\n");
		printf("*************************************************************************************************************\n");
		printf("You Are Connected to the server \n");
		//Inform the server that the player has joined the lobby
		sprintf(sendbuf, "%s", "has joined the lobby", clock());

////////////////////////////////////////////////////////////////////////////////////////////////////
//Set up the structure that will be used to gain the IP address and set the sockets type
////////////////////////////////////////////////////////////////////////////////////////////////////
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		//get the IP Address
		iResult = getaddrinfo(serverName, DEFAULT_PORT, &hints, &addressList);
		//	ipBuff = getaddrinfo(serverName, DEFAULT_PORT, &hints, &addressList);
		printf("Your IP Address: %d\n", &addressList);
		printf("\n");
		//Send the IP address of the client to the server 
		//sprintf(ipBuff, "Player 1 IP Address: ", "%i", clock());
		if (iResult != 0)
		{
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return 1;

		}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Loop through the address list
////////////////////////////////////////////////////////////////////////////////////////////////////
		for (ptr = addressList; ptr != NULL; ptr = ptr->ai_next)
		{
////////////////////////////////////////////////////////////////////////////////////////////////////
//Connect to the socket opened on the server side
////////////////////////////////////////////////////////////////////////////////////////////////////
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);


			if (ConnectSocket == INVALID_SOCKET)
			{
				printf("Error at Socket(): %ld\n", WSAGetLastError());
				freeaddrinfo(addressList);
				WSACleanup();
				return 1;
			}


			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Prevent the memory leak from occuring
////////////////////////////////////////////////////////////////////////////////////////////////////
		freeaddrinfo(addressList);
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Unable to connect to the server!: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Send the information to the server
////////////////////////////////////////////////////////////////////////////////////////////////////
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf) + 1, 0);
		//ipBuff = send(ConnectSocket, ipBuff, (int)strlen(ipBuff) + 1, 0);
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;


		}


		printf("Bytes sent: %ld\n", iResult);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Shutdown the connection 
////////////////////////////////////////////////////////////////////////////////////////////////////
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			printf("Shutdown failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}


		/*do
		{*/
////////////////////////////////////////////////////////////////////////////////////////////////////
//Listen for a message from the server
////////////////////////////////////////////////////////////////////////////////////////////////////
			iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
			{
				printf("Bytes Received: %d MSG =%s\n", iResult, recvbuf);

			}
			else
				if (iResult == 0)
				{
					printf("Connection Closed \n");

				}
				else
				{
					printf("Recv failed: %d\n", WSAGetLastError());




				}/*while (iResult > 0);*/


				//Close the socket 
				closesocket(ConnectSocket);



		

	//Clean up after the session
	WSACleanup();
	return 0;
}