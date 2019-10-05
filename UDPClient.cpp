#include "stdafx.h"
#include "UDPClient.h"


UDPClient::UDPClient()
{
}


UDPClient::~UDPClient()
{
}

int UDPClient::connect()
{



	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET UDPServer = INVALID_SOCKET;

	/*if (strcmp(argv[1], "-client") == 0)
	{*/




	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; //Use Datagram for UDP
	hints.ai_protocol = IPPROTO_UDP;

	iResult = getaddrinfo(serverName, DEFAULT_PORT, &hints, &addressList);

	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	if (addressList != NULL)
	{
		UDPServer = socket(addressList->ai_family, addressList->ai_socktype, addressList->ai_protocol);

		if (UDPServer == INVALID_SOCKET)
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(addressList);
			WSACleanup();
			return 1;
		}



		iResult = sendto(UDPServer, sendbuf, (int)strlen(sendbuf) + 1, 0, addressList->ai_addr, (int)addressList->ai_addr);

		if (iResult == SOCKET_ERROR)
		{
			printf("Send failed: %d\n", WSAGetLastError());
			freeaddrinfo(addressList);
			closesocket(UDPServer);
			WSACleanup();
			return 1;
		}

		printf("Bytes sent: %ld\n", iResult);

		sockaddr client_addr;
		int iClientAddrLen = sizeof(client_addr);
		iResult = getsockname(UDPServer, (SOCKADDR *)&client_addr, &iClientAddrLen);

		if (iResult == SOCKET_ERROR)
		{
			printf("getsockname failed: %d\n", WSAGetLastError());
			freeaddrinfo(addressList);
			closesocket(UDPServer);
			WSACleanup();
			return 1;
		}
		freeaddrinfo(addressList);
		iResult = recvfrom(UDPServer, recvbuf, recvbuflen, 0, NULL, NULL);


	}
	printf("Bytes Received: %d MSG= %s\n", iResult, recvbuf);
	
	/*}*/
		// cleanup
	closesocket(UDPServer);



	WSACleanup();

	return 0;
}

//
//void UDPClient::SendMessage()
//{
////	char *sendbuf2[100];
//	unsigned char sendbuf2[1000];
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	SOCKET UDPServer = INVALID_SOCKET;
//	MSG_STRUCT msg;
//	msg.code = MSGCODE;
//	msg.length = 0;                         // Fill this in later when we pack message.
//	strcpy((char*)msg.username, "Mike");
//	msg.longValue = 0x12345678;
//	msg.shortvalue = 0x1234;
//	msg.byteValue = 0x12;
//	msg.PlayerPositionX = -22;
//	unsigned short buflen;
//
//	// Now pack the message structure into the send buffer.
//	*sendbuf2 = PackMsg(&msg, sendbuf2);
//	printf("Message being sent: code:%i\n usr:%s\n l:0x%x s:0x%x b:0x%x i:%i\n datalen:%i\n",
//		msg.code,
//		msg.username,
//		msg.longValue, msg.shortvalue, msg.byteValue, msg.PlayerPositionX,
//		msg.datalen);
//
//
//
//
//
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_DGRAM; //Use Datagram for UDP
//	hints.ai_protocol = IPPROTO_UDP;
//
//	iResult = getaddrinfo(serverName, DEFAULT_PORT, &hints, &addressList);
//
//	if (addressList != NULL)
//	{
//		UDPServer = socket(addressList->ai_family, addressList->ai_socktype, addressList->ai_protocol);
//
//		iResult = sendto(UDPServer,
//			(char *)sendbuf,
//			(int)buflen,
//			0,							// flags - we never need them so zero them
//			addressList->ai_addr,
//			(int)addressList->ai_addrlen);
//
//		printf("Bytes sent: %ld\n", iResult);
//
//		sockaddr client_addr;
//		int iClientAddrLen = sizeof(client_addr);
//		iResult = getsockname(UDPServer, (SOCKADDR *)&client_addr, &iClientAddrLen);
//
//
//	}
//
//	closesocket(UDPServer);
//
//	
//
//	WSACleanup();
//
//	
//}
//
//
//void UDPClient::SendUpdate()
//{
//	char sendbuf[1000];
//	sprintf(sendbuf, "%s", "Player 1 has made a move", clock());
//	//sprintf(sendbuf, "Player:%i Made a Move", );
//	SendMessage();
//	return;
//
//}
//
//void UDPClient::SendUpdate2()
//{
//	char sendbuf2[1000];
//	
//	sprintf(sendbuf2, "%s", "Player 2 has made a move", clock());
//	//sprintf(sendbuf, "Player:%i Made a Move", );
//	SendMessage();
//	return;
//}
//
//void UDPClient::SendBoardUpdate(int posX, int posY)
//{
//	unsigned char* sendbuf[1000];
//
//	//sprintf(sendbuf, "X:%i ,Y %i,", posX, posY);
//	//SendMessage(sendbuf);
//	return;
//
//}
///////////////////////////////////////////////////////////////////////////////////
/////Send Packet of Data
///////////////////////////////////////////////////////////////////////////////////
void UDPClient::SendPacking(int posX, int posY)
{
	TicTacToe MyGame;
	unsigned char sendbuf2[1000];
	char	recvbuf2[DEFAULT_BUFLEN];
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET UDPServer = INVALID_SOCKET;
	MSG_STRUCT msg;
	msg.code = MSGCODE;
	msg.length = 0;                         // Fill this in later when we pack message.
	strcpy((char*)msg.username, "Player 2");
	msg.longValue = 0x12345678;
	msg.shortvalue = 0x1234;
	msg.byteValue = 0x12;
	msg.PlayerPositionX = posX;
	msg.PlayerPositionY = posY;
	msg.playerTurn = 2;
	msg.datalen = 100;
	unsigned short buflen;

	// Now pack the message structure into the send buffer.
	buflen = PackMsg(&msg, sendbuf2);
	printf("*******************************Message Sent****************************************");
	printf("\n");
	printf("code:%i\n User:%s\n Player Position:X:%i\n Player Position Y:%i\n datalen:%i\n",
		msg.code,
		msg.username,
		msg.PlayerPositionX,
		msg.PlayerPositionY,
		msg.playerTurn,
		msg.datalen);
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; //Use Datagram for UDP
	hints.ai_protocol = IPPROTO_UDP;

	iResult = getaddrinfo(serverName, DEFAULT_PORT, &hints, &addressList);

	if (addressList != NULL)
	{
		UDPServer = socket(addressList->ai_family, addressList->ai_socktype, addressList->ai_protocol);

		iResult = sendto(UDPServer,
			(char *)sendbuf2,
			(int)buflen,
			0,							// flags - we never need them so zero them
			addressList->ai_addr,
			(int)addressList->ai_addrlen);

		printf("Bytes sent: %ld\n", iResult);

		sockaddr client_addr;
		int iClientAddrLen = sizeof(client_addr);
		iResult = getsockname(UDPServer, (SOCKADDR *)&client_addr, &iClientAddrLen);

		//printf("Client Addr %s:%d\n", inet_ntoa(client_addr.), client_addr.sin_port);
iResult = recvfrom(UDPServer,
			recvbuf,
			recvbuflen,
			0,			// flags we don't need, so set to zero
			NULL,
			NULL);
//receive pack from the server containing updated position of player 2
		UnpackMSG(&msg,(unsigned char*)recvbuf);
		printf("*********************Message received************************");
		printf("\n");
		printf("code:%i\n New Player Position:X:%i New Player Position Y:%i\n Player Turn: %i\n  datalen:%i\n",
			msg.code,
			msg.PlayerPositionX,
			msg.PlayerPositionY,
			msg.playerTurn,
			msg.datalen);

		//Update the position of the latest position
		MyGame.SetPlayerX(msg.PlayerPositionX);
		MyGame.SetPlayerY(msg.PlayerPositionY);
		






	freeaddrinfo(addressList);
		printf("Bytes received: %d Msg=%s\n", iResult, recvbuf);
	}

	closesocket(UDPServer);



	WSACleanup();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will pack the contents of the message before sending to the user
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned short UDPClient::PackMsg(MSG_STRUCT * msg, unsigned char * buff)
{
	unsigned short msglen;
	unsigned char *lenptr;

	PackShort(buff, msg->code);
	lenptr = buff;
	buff += sizeof(unsigned short);
	PackBytes(buff, msg->username, 20);
	PackLong(buff, msg->longValue);
	PackShort(buff, msg->shortvalue);
	PackByte(buff, msg->byteValue);
	PackLong(buff, msg->PlayerPositionX);
	PackLong(buff, msg->PlayerPositionY);
	PackLong(buff, msg->playerTurn);
	PackShort(buff, msg->datalen);
	PackBytes(buff, msg->data, msg->datalen);


	msglen = sizeof(unsigned short)
		+ sizeof(unsigned short)
		+ sizeof(msg->username)
		+ sizeof(unsigned long)
		+ sizeof(unsigned short)
		+ 1
		+ sizeof(unsigned long)
		+ sizeof(unsigned short)
		+ msg->datalen;

	PackShort(lenptr, msglen);
	return msglen;








}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will pack the contents of the message before sending to the user
////////////////////////////////////////////////////////////////////////////////////////////////////
void UDPClient::UnpackMSG(MSG_STRUCT * msg, unsigned char * buff)
{
	UnpackShort(buff, msg->code);
	UnpackShort(buff, msg->length);
	UnpackBytes(buff, msg->username, 20);
	UnpackLong(buff, msg->longValue);
	UnpackShort(buff, msg->shortvalue);
	UnpackByte(buff, msg->byteValue);
	UnpackLong(buff, msg->PlayerPositionX);
	UnpackLong(buff, msg->PlayerPositionY);
	UnpackLong(buff, msg->playerTurn);
	UnpackShort(buff, msg->datalen);
	UnpackBytes(buff, msg->data, msg->datalen);

}
