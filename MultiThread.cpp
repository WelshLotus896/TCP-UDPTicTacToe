#include "stdafx.h"
#include "MultiThread.h"


MultiThread::MultiThread()
{
}


MultiThread::~MultiThread()
{
}

DWORD MultiThread::UDPServerThreadProc(LPVOID SerlpParameter)
{
	UDPServerparam = (DWORD)SerlpParameter;
	UDPServerIndex = 0;
	UDPServer myUDPServer;

	printf("UDP Server Starting, UDPServerParam = %d\r\n", UDPServerparam);

	for (int i = 0; i < 9; i++)
	{

/////////////////////////////////////////////////////////////////////////////////////////////
//Listen for any update messages for the the game board
////////////////////////////////////////////////////////////////////////////////////////////
		myUDPServer.ReceiveBoardUpdate();
	
	
		
	}
		
	
	
	return 0;
}

int MultiThread::MultiThreadMain()
{

	printf("Process ID = %x\r\n", GetCurrentProcessId());
	printf("Thread ID = %x\r\n", GetCurrentThreadId());


	while (1)
	{
		ThreadHdl = CreateThread(NULL, 0, UDPServerThreadProc, (LPVOID)param, 0, &Threadid);
		getchar();
	}



TerminateThread(ThreadHdl, 0);

CloseHandle(ThreadHdl);

printf("\r\n Terminating Threads \r\n");

	return 0;
}
