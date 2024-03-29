#pragma once
#include "stdafx.h"

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512
class TCPServer3
{
private: 
	WSADATA	wsaData;
	WSADATA	wsaData2;
	char	recvbuf[DEFAULT_BUFLEN];
	char	recvbuf2[DEFAULT_BUFLEN];
	int		iResult;
	int	    iResult2;
	int		recvbuflen = DEFAULT_BUFLEN;
	int		recvbuflen2 = DEFAULT_BUFLEN;
	int playerCount = 0;
	struct addrinfo *addressList = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	struct addrinfo *addressList2 = NULL;
	struct addrinfo *ptr2 = NULL;
	struct addrinfo hints2;


	char userNamebuf[DEFAULT_BUFLEN];
	char userNamebuf2[DEFAULT_BUFLEN];
	char responseBuf[DEFAULT_BUFLEN];
	//For player 1 
	SOCKET ListenSocket1 = INVALID_SOCKET;
	//For Player 2
	SOCKET ListenSocket2 = INVALID_SOCKET;
	
	//For Player 1
	SOCKET ClientSocket1 = INVALID_SOCKET;
	//For Player 2
	SOCKET ClientSocket2 = INVALID_SOCKET;
	int iRcvdBytes = 0;
	int iRcvdBytes2 = 0;
	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	BOOL bOptVal2 = TRUE;
	int bOptLen2 = sizeof(BOOL);


public:
	TCPServer3();
	~TCPServer3();
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the sockets for Player 1
////////////////////////////////////////////////////////////////////////////////////////////////////
	int createSocket(void);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the sockets for Player 2
////////////////////////////////////////////////////////////////////////////////////////////////////	
	int createSocket2(void);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Recieve player 1
////////////////////////////////////////////////////////////////////////////////////////////////////
	int recievePlayer1(void);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Recieve player 2
////////////////////////////////////////////////////////////////////////////////////////////////////
	int recievedPlayer2(void);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the connection
////////////////////////////////////////////////////////////////////////////////////////////////////	
	int createConnection(void);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Close the socket 
////////////////////////////////////////////////////////////////////////////////////////////////////
	int closeSocket(void);
};

