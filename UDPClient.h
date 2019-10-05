#pragma once
#include "Semaphore.h"
#include "TicTacToe.h"
#define MSGCODE 0x0001
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

class UDPClient
{
public:
	WSADATA	wsaData;
	char	recvbuf[DEFAULT_BUFLEN];
	int		iResult;
	int		recvbuflen = DEFAULT_BUFLEN;
	
	struct addrinfo *addressList = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;
	SOCKET UDPServer = INVALID_SOCKET;
	char* serverName = "127.0.0.1";
	char *sendbuf = "this is a test";
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//Create the data structure for the message 
	////////////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct
	{
		unsigned short code;
		unsigned short length;
		unsigned char username[50];
		unsigned long longValue;
		unsigned short shortvalue;
		unsigned char byteValue;
		int PlayerPositionX;
		int PlayerPositionY;
		int playerTurn;
		unsigned short datalen;
		unsigned char data[100];

	}MSG_STRUCT;
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the macros required for packing the message
////////////////////////////////////////////////////////////////////////////////////////////////////
#define PackBytes(bf, bytes, len) \
    memcpy(bf, bytes, len); \
    bf += len;

#define PackLong(bf, l) \
    *bf++ = (l >> 24) & 0xFF; \
    *bf++ = (l >> 16) & 0xFF; \
    *bf++ = (l >> 8) & 0xFF; \
    *bf++ = l & 0xFF;    

#define PackShort(bf, s) \
    *bf++ = (s >> 8) & 0xFF; \
    *bf++ = s & 0xFF;    

#define PackByte(bf, b) \
    *bf++ = b;    

	// UNPACKING
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create the macros for unpacking the messages contents
////////////////////////////////////////////////////////////////////////////////////////////////////
#define UnpackBytes(bf, bytes, len) \
    memcpy(bytes, bf, len); \
    bf += len;

#define UnpackLong(bf, l) \
    l = (*bf++ << 24); \
    l += (*bf++ << 16); \
    l += (*bf++ << 8); \
    l += *bf++;

#define UnpackShort(bf, s) \
    s = (*bf++ << 8); \
    s += *bf++;

#define UnpackByte(bf, b) \
    b = *bf++;



public:
	UDPClient();
	~UDPClient();
	int connect();

	
	/*void SendMessage();
	void SendUpdate();
	void SendUpdate2();
	void SendBoardUpdate(int posX, int posY);*/
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will send the contents of the message
////////////////////////////////////////////////////////////////////////////////////////////////////
	void SendPacking(int posX, int posY);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will pack the contents of the message before sending to the user
////////////////////////////////////////////////////////////////////////////////////////////////////
	unsigned short PackMsg(MSG_STRUCT *msg, unsigned char *buff);
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will pack the contents of the message before sending to the user
////////////////////////////////////////////////////////////////////////////////////////////////////
	void UnpackMSG(MSG_STRUCT *msg, unsigned char *buff);
};

