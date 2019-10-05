#include "stdafx.h"
#include "TCPServer3.h"
#include "UDPServer.h"
#include "MultiThread.h"
#include "Semaphore.h"
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512
int _tmain(int argc, _TCHAR* argv[])
{
///////////////////////////////////////////////////////////////////////////
///////Create objects for the client and server 
///////////////////////////////////////////////////////////////////////////
	TCPServer3 myServer;
	
	MultiThread myThread;
	Semaphore mySemaphore;
	char key; // input key
	int UDPClient;
	printf("*********************************************************************************************************************************\n");
	printf("****************************************************** Hardhugadr 1.0 ***********************************************************\n");
	printf("*********************************************************************************************************************************\n");
	
///////////////////////////////////////////////////////////////////////////
///////Create two sockets for the clients to connect to
///////////////////////////////////////////////////////////////////////////
	myServer.createSocket();
	myServer.createSocket2();
///////////////////////////////////////////////////////////////////////////
///////Initiate the Multithreading Phase 
///////////////////////////////////////////////////////////////////////////
	printf("UDP Client Initiated \n");
	myThread.MultiThreadMain();

	return 0;
}