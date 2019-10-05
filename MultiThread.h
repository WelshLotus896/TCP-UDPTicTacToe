#pragma once
#include "stdafx.h"
#include "MultiThread.h"
//#include "TicTacToe.h"
#include "UDPServer.h"
//Game Thread Variables
static HANDLE  ThreadHdl;
static DWORD   Threadid;
static int     Index;
static DWORD	param;

//UDP Server Thread Variables
static HANDLE  UDPServerThreadHdl;
static DWORD   UDPServerThreadid;
static int     UDPServerIndex;
static DWORD	UDPServerparam;


class MultiThread
{
public:
	MultiThread();
	~MultiThread();
	//static DWORD WINAPI GameThreadProc(LPVOID lpParameter);
	static DWORD WINAPI UDPServerThreadProc(LPVOID SerlpParameter);
	static	int MultiThreadMain();
};

