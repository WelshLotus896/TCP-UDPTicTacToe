#include "stdafx.h"
#include "UDPServer.h"


UDPServer::UDPServer()
{
}


UDPServer::~UDPServer()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the sockets for Player 1
////////////////////////////////////////////////////////////////////////////////////////////////////
int UDPServer::createSocket1(void)
{
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	int iRcvdBytes = 0;
	sockaddr_in rx_addr;
	sockaddr_in sender_addr;
	int iSenderAddrSize = sizeof(sender_addr);
	myUDPServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //set the socket up 
	printf("Listening for Client 1 Connection... \n");





	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the sockets for Player 2
////////////////////////////////////////////////////////////////////////////////////////////////////
int UDPServer::createSocket2(void)
{
	iResult2 = WSAStartup(MAKEWORD(2, 2), &wsaData2);
	int iRcvdBytes2 = 0;
	sockaddr_in rx_addr2;
	sockaddr_in sender_addr2;
	int iSenderAddrSize2 = sizeof(sender_addr2);
	myUDPServer2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //set the socket up 

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the connection for the first client
////////////////////////////////////////////////////////////////////////////////////////////////////
int UDPServer::client1Connection()
{

	rx_addr.sin_family = AF_INET; //set the family 
	rx_addr.sin_port = htons((u_short)atol(DEFAULT_PORT));
	rx_addr.sin_addr.s_addr = htonl(INADDR_ANY); //listen for any port address
	iResult = bind(myUDPServer, (SOCKADDR*)&rx_addr, sizeof(rx_addr));
	//Who is the sender

	iResult = recvfrom(myUDPServer, recvbuf, recvbuflen, 0, (SOCKADDR *)&sender_addr, &iSenderAddrSize);

	printf("Bytes recieved: %d MSG = %s\n", iResult, recvbuf);
	printf("Player 1 Connected... \n");
	printf("Waiting For Second Client... \n");

	//Send to original sender
	iResult = sendto(myUDPServer, recvbuf, iResult, 0, (SOCKADDR*)&sender_addr, iSenderAddrSize);
	//Print how many bytes were sent to the reciever
	printf("Bytes Sent: %ld\n", iResult);
	printf("*********************************************************\n");
	//Close the socket to tidy up
	closesocket(myUDPServer);
	return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the connection for the second client
////////////////////////////////////////////////////////////////////////////////////////////////////
int UDPServer::client2Connection()
{
	printf("************************************************************\n");
	printf("Listening for Connection for Client 2...\n");

	rx_addr2.sin_family = AF_INET; //set the family 
	rx_addr2.sin_port = htons((u_short)atol(DEFAULT_PORT));
	rx_addr2.sin_addr.s_addr = htonl(INADDR_ANY); //listen for any port address
	iResult2 = bind(myUDPServer2, (SOCKADDR*)&rx_addr2, sizeof(rx_addr2));
	//Who is the sender
	iResult2 = recvfrom(myUDPServer2, recvbuf2, recvbuflen2, 0, (SOCKADDR *)&sender_addr2, &iSenderAddrSize2);
	printf("Player 2 Connected... \n");
	printf("Bytes recieved: %d MSG = %s\n", iResult2, recvbuf2);
	iResult2 = sendto(myUDPServer2, recvbuf2, iResult2, 0, (SOCKADDR*)&sender_addr2, iSenderAddrSize2);
	//Print how many bytes were sent to the reciever
	printf("Bytes Sent: %ld\n", iResult2);
	printf("*********************************************************\n");
	closesocket(myUDPServer);
	return 1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Recieve Board Update during game time
////////////////////////////////////////////////////////////////////////////////////////////////////
void UDPServer::ReceiveBoardUpdate()
{
	unsigned char sendbuf2[1000];
	SOCKET UDPServer2 = INVALID_SOCKET;
	char	recvbuff2[DEFAULT_BUFLEN];
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	int iRcvdBytes = 0;
	sockaddr_in rx_addr;
	sockaddr_in sender_addr;
	MSG_STRUCT msg;
	int iSenderAddrSize = sizeof(sender_addr);
	UDPServer2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //set the socket up 
	printf("Listening for the board... \n");
	
	rx_addr.sin_family = AF_INET; //set the family 
	rx_addr.sin_port = htons((u_short)atol(DEFAULT_PORT));
	rx_addr.sin_addr.s_addr = htonl(INADDR_ANY); //listen for any port address
	
	iResult = bind(UDPServer2, (SOCKADDR*)&rx_addr, sizeof(rx_addr));
	iResult = recvfrom(UDPServer2, recvbuff2, recvbuflen, 0, (SOCKADDR *)&sender_addr, &iSenderAddrSize);
	
	UnpackMSG(&msg,(unsigned char*)recvbuff2);
	
	printf("*********************Message received************************");
	printf("\n");
	printf("Message received: %d bytes code:%i\n User:%s\n  Player Position:X:%i Player Position Y:%i\n Player Turn: %i\n  datalen:%i\n",
		iResult, msg.code,
		msg.username,
		msg.PlayerPositionX,
		msg.PlayerPositionY,
		msg.playerTurn,
		msg.datalen);
	printf("*************************************************************\n");
	//strcpy(recvbuff2, "Message Receieved, Updating Board\n");
	//iResult = strlen(recvbuff2) + 1;

	//pack the message
	buflen = PackMsg(&msg, sendbuf2);
	printf("*******************************Message Sent****************************************");
	printf("\n");
	//Send to original sender
	iResult = sendto(UDPServer2,
		recvbuff2,
		iResult,
		0,							// flags - we never need them so zero them
		(SOCKADDR *)&sender_addr,
		iSenderAddrSize);

	printf("Response Sent: %ld Msg=%s\n", iResult, recvbuff2);
	myGame.SetPlayerX(msg.PlayerPositionX);
	myGame.SetPlayerY(msg.PlayerPositionY);
	myGame.SetPlayerTurn(msg.playerTurn);
	myGame.initBoard();

	printf("Bytes Sent: %ld\n", iResult);
	
	printf("*********************************************************\n");
	//Close the socket to tidy up
	closesocket(UDPServer2);
	WSACleanup();

	return;
}
//
//void UDPServer::RecieveUpdate()
//{
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	int iRcvdBytes = 0;
//	sockaddr_in rx_addr;
//	sockaddr_in sender_addr;
//	int iSenderAddrSize = sizeof(sender_addr);
//	myUDPServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //set the socket up 
//	printf("Listening for Game Messages... \n");
//
//	rx_addr.sin_family = AF_INET; //set the family 
//	rx_addr.sin_port = htons((u_short)atol(DEFAULT_PORT));
//	rx_addr.sin_addr.s_addr = htonl(INADDR_ANY); //listen for any port address
//	iResult = bind(myUDPServer, (SOCKADDR*)&rx_addr, sizeof(rx_addr));
//	//Who is the sender
//	//ReceiveString(myUDPServer, recvbuf, 1000);
//	iResult = recvfrom(myUDPServer, recvbuf, recvbuflen, 0, (SOCKADDR *)&sender_addr, &iSenderAddrSize);
//
//	printf("Bytes recieved: %d MSG = %s\n", iResult, recvbuf);
//	//Send to original sender
//	iResult = sendto(myUDPServer, recvbuf, iResult, 0, (SOCKADDR*)&sender_addr, iSenderAddrSize);
//	//Print how many bytes were sent to the reciever
//	printf("Bytes Sent: %ld\n", iResult);
//	printf("*********************************************************\n");
//	//Close the socket to tidy up
//	closesocket(myUDPServer);
//	
//	
//	return;
//}
//
//void UDPServer::RecieveUpdate2()
//{
//	
//	iResult2 = WSAStartup(MAKEWORD(2, 2), &wsaData2);
//	int iRcvdBytes2 = 0;
//	sockaddr_in rx_addr2;
//	sockaddr_in sender_addr2;
//	int iSenderAddrSize2 = sizeof(sender_addr2);
//	myUDPServer2 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //set the socket up 
//	printf("Listening for Game Messages... \n");
//
//	rx_addr2.sin_family = AF_INET; //set the family 
//	rx_addr2.sin_port = htons((u_short)atol(DEFAULT_PORT));
//	rx_addr2.sin_addr.s_addr = htonl(INADDR_ANY); //listen for any port address
//	iResult2 = bind(myUDPServer2, (SOCKADDR*)&rx_addr2, sizeof(rx_addr));
//	//Who is the sender
//	ReceiveString(myUDPServer2, recvbuf3, 1000);
//	//iResult = recvfrom(myUDPServer, recvbuf, recvbuflen, 0, (SOCKADDR *)&sender_addr, &iSenderAddrSize);
//
//	printf("Bytes recieved: %d MSG = %s\n", iResult, recvbuf);
//
//	//Send to original sender
//	//iResult = sendto(myUDPServer, recvbuf, iResult, 0, (SOCKADDR*)&sender_addr, iSenderAddrSize);
//	//Print how many bytes were sent to the reciever
//	//printf("Bytes Sent: %ld\n", iResult);
//	printf("*********************************************************\n");
//	//Close the socket to tidy up
//	closesocket(myUDPServer2);
//
//
//	return;
//}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will pack the contents of the message before sending to the user
////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned short UDPServer::PackMsg(MSG_STRUCT * msg, unsigned char * buff)
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
void UDPServer::UnpackMSG(MSG_STRUCT * msg, unsigned char * buff)
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
