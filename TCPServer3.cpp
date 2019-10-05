#include "stdafx.h"
#include "TCPServer3.h"


TCPServer3::TCPServer3()
{
}


TCPServer3::~TCPServer3()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to create the socket for the first player to connect to
////////////////////////////////////////////////////////////////////////////////////////////////////
int TCPServer3::createSocket(void)
{

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}




	printf("Starting server...\r\n");



	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &addressList);

	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	
	// Create a SOCKET for connecting to server
	ListenSocket1 = socket(addressList->ai_family, addressList->ai_socktype, addressList->ai_protocol);

	if (ListenSocket1 == INVALID_SOCKET)
	{
		printf("socket failed: %ld\n", WSAGetLastError());
		freeaddrinfo(addressList);
		WSACleanup();
		return 1;
	}

	


		setsockopt(ListenSocket1, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen);

	
		
		if (setsockopt(ListenSocket1, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal, bOptLen) == SOCKET_ERROR)
	{
		printf("setsockopt failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket1);
		WSACleanup();
		return 1;
	}



	iResult = bind(ListenSocket1, addressList->ai_addr, (int)addressList->ai_addrlen);
	
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed: %d\n", WSAGetLastError());
		freeaddrinfo(addressList);
		closesocket(ListenSocket1);
		WSACleanup();
		return 1;
	}



	
	freeaddrinfo(addressList);
	recievePlayer1();
	sprintf(responseBuf, "%s", "Two Players are connected, Please Press a Key To begin", clock());
	//createConnection();
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to create the socket for the second player to connect to
////////////////////////////////////////////////////////////////////////////////////////////////////
int TCPServer3::createSocket2(void)
{

	iResult2 = WSAStartup(MAKEWORD(2, 2), &wsaData2);
	if (iResult2 != 0)
	{
		printf("WSAStartup failed: %d\n", iResult2);
		return 1;
	}
	ZeroMemory(&hints2, sizeof(hints2));
	hints2.ai_family = AF_INET;
	hints2.ai_socktype = SOCK_STREAM;
	hints2.ai_protocol = IPPROTO_TCP;
	hints2.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult2 = getaddrinfo(NULL, DEFAULT_PORT, &hints2, &addressList2);

	if (iResult2 != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult2);
		WSACleanup();
		return 1;
	}

	ListenSocket2 = socket(addressList2->ai_family, addressList2->ai_socktype, addressList2->ai_protocol);

	if (ListenSocket2 == INVALID_SOCKET)
	{
		printf("socket failed: %ld\n", WSAGetLastError());
		freeaddrinfo(addressList);
		WSACleanup();
		return 1;
	}

	setsockopt(ListenSocket2, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal2, bOptLen2);

	if (setsockopt(ListenSocket2, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptVal2, bOptLen2) == SOCKET_ERROR)
	{
		printf("setsockopt failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket2);
		WSACleanup();
		return 1;
	}


	iResult2 = bind(ListenSocket2, addressList2->ai_addr, (int)addressList2->ai_addrlen);
	if (iResult2 == SOCKET_ERROR)
	{
		printf("bind failed: %d\n", WSAGetLastError());
		freeaddrinfo(addressList2);
		closesocket(ListenSocket1);
		WSACleanup();
		return 1;
	}

	if (iResult2 == SOCKET_ERROR)
	{
		printf("bind failed: %d\n", WSAGetLastError());
		freeaddrinfo(addressList2);
		closesocket(ListenSocket2);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(addressList2);
	recievedPlayer2();
	//sprintf(responseBuf, "%s", "Two Players are connected, Please Press a Key To begin", clock());
	//int iResponse = send(ClientSocket1, responseBuf, iRcvdBytes, 0);
	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to recieve the first player
////////////////////////////////////////////////////////////////////////////////////////////////////
int TCPServer3::recievePlayer1(void)
{
	printf("Listening for connection........ \r\n"); //listen for connection for the client

	iResult = listen(ListenSocket1, SOMAXCONN);
	//while (!_kbhit())        // Loop until key pressed
	//{

		if (iResult == SOCKET_ERROR)
		{
			printf("listen failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket1);
			WSACleanup();
			return 1;
		}


		ClientSocket1 = accept(ListenSocket1, NULL, NULL);
		if (ClientSocket1 == INVALID_SOCKET)
		{
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket1);
			WSACleanup();
			return 1;
		}


		//Do while the i result is less than 0


			//iResult = recv(ClientSocket, userNamebuf, recvbuflen, 0);
			iResult = recv(ClientSocket1, recvbuf, recvbuflen, 0);
			//Recieve the second player

			if (iResult > 0)
			{
				printf("Bytes received: %d Msg = %s\n", iResult, recvbuf);
				printf("1 More Player Required....\n");
				playerCount++; //Increase the player Count
				printf("Players: %d\n", playerCount);
				iRcvdBytes = iResult;
			}
			else if (iResult == 0)
				printf("Connection closing...\n");
			else
			{
				printf("recv failed: %d\n", WSAGetLastError());
				closesocket(ClientSocket1);
				WSACleanup();
				return 1;
			}

			if (playerCount == 2)
			{
				printf("*********************************************************************************************************************************\n");
				printf("Maximum Players requirements met \n");
				printf("Commencing Stage 2 \n");
				printf("Multithreading and UDP initiated \n");
				//Send a message to the Client 1 to press a Key to start the UDP 
				
				
			}
		

		// Echo the buffer back to the sender
		iResult = send(ClientSocket1, recvbuf, iRcvdBytes, 0);
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ClientSocket1);
			WSACleanup();
			return 1;
		}

		printf("Bytes Sent: %ld\n", iResult);
		printf("*********************************************************************************************************************************\n");

		iResult = shutdown(ClientSocket1, SD_SEND);
		////iResult2 = shutdown(ClientSocket2, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(ClientSocket1);
			WSACleanup();
			return 1;
		}

		// cleanup
		closesocket(ClientSocket1);
	/*}*/
	closesocket(ListenSocket1);

	
	//closeSocket();
	}



////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to recieve the second player
////////////////////////////////////////////////////////////////////////////////////////////////////
int TCPServer3::recievedPlayer2(void)
{
	printf("Listening for client 2 connection........ \r\n"); //listen for connection for the client


	iResult2 = listen(ListenSocket2, SOMAXCONN);


	if (iResult2 == SOCKET_ERROR)
	{
		printf("listen failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket2);
		WSACleanup();
		return 1;
	}


	ClientSocket2 = accept(ListenSocket2, NULL, NULL);
	if (ClientSocket2 == INVALID_SOCKET)
	{
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket2);
		WSACleanup();
		return 1;
	}


	
		//iResult = recv(ClientSocket, userNamebuf, recvbuflen, 0);
		iResult2 = recv(ClientSocket2, recvbuf2, recvbuflen2, 0);
		//Recieve the second player

		if (iResult2 > 0)
		{
			printf("Bytes received: %d Msg = %s\n", iResult2, recvbuf2);
			printf("1 More Player Required....\n");
			playerCount++; //Increase the player Count
			printf("Players: %d\n", playerCount);
			iRcvdBytes2 = iResult2;
		}


		if (playerCount == 2)
		{
			printf("*********************************************************************************************************************************\n");
			printf("Maximum Players requirements met \n");
			printf("Commencing Stage 2 \n");
			printf("Multithreading and UDP initiated \n");
			
		}
	

	// Echo the buffer back to the sender
	iResult2 = send(ClientSocket2, recvbuf2, iRcvdBytes2, 0);
	if (iResult2 == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket2);
		WSACleanup();
		return 1;
	}
	closesocket(ClientSocket2);
	closesocket(ListenSocket2);
	printf("Bytes Sent: %ld\n", iResult2);
	printf("*********************************************************************************************************************************\n");
	

}
//closesocket(ListenSocket);


int TCPServer3::createConnection(void)
{
	printf("Listening for connection........ \r\n"); //listen for connection for the client
	
	iResult = listen(ListenSocket1, SOMAXCONN);
	while (!_kbhit())        // Loop until key pressed
	{
		
		if (iResult == SOCKET_ERROR)
		{
			printf("listen failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket1);
			WSACleanup();
			return 1;
		}


		ClientSocket1 = accept(ListenSocket1, NULL, NULL);
		if (ClientSocket1 == INVALID_SOCKET)
		{
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket1);
			WSACleanup();
			return 1;
		}


		do
		{
			//iResult = recv(ClientSocket, userNamebuf, recvbuflen, 0);
			iResult = recv(ClientSocket1, recvbuf, recvbuflen, 0);
			//Recieve the second player

			if (iResult > 0)
			{
				printf("Bytes received: %d Msg = %s\n", iResult, recvbuf);
				printf("1 More Player Required....\n");
				playerCount++; //Increase the player Count
				printf("Players: %d", playerCount);
				iRcvdBytes = iResult;
			}
			else if (iResult == 0)
				printf("Connection closing...\n");
			else
			{
				printf("recv failed: %d\n", WSAGetLastError());
				closesocket(ClientSocket1);
				WSACleanup();
				return 1;
			}

			if (playerCount == 2)
			{
				printf("*********************************************************************************************************************************\n");
				printf("Maximum Players requirements met \n");
				printf("Commencing Stage 2 \n");
				printf("Multithreading and UDP initiated \n");
			}
		} while (iResult > 0);

		// Echo the buffer back to the sender
		iResult = send(ClientSocket1, recvbuf, iRcvdBytes, 0);
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ClientSocket1);
			WSACleanup();
			return 1;
		}

		printf("Bytes Sent: %ld\n", iResult);
		printf("*********************************************************************************************************************************\n");

		//iResult = shutdown(ClientSocket1, SD_SEND);
		////iResult2 = shutdown(ClientSocket2, SD_SEND);
		//if (iResult == SOCKET_ERROR)
		//{
		//	printf("shutdown failed: %d\n", WSAGetLastError());
		//	closesocket(ClientSocket1);
		//	WSACleanup();
		//	return 1;
		//}

		// cleanup
		//closesocket(ClientSocket);
	}
	//closesocket(ListenSocket);

	printf("\r\nHit key to exit");
	while (!_kbhit());
	//closeSocket();
}

int TCPServer3::closeSocket(void)
{
	WSACleanup();

	return 0;
}
