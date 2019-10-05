#pragma once
#include "stdafx.h"
#include "TicTacToe.h"
static int terminate_app1;
static LONG    semaphoreCount;
static LPCTSTR semaphorename = (LPCTSTR)"GameThread";
static char key = 'a';

static HANDLE  semaphorehdl;
static LONG    semaphorecount;
static HANDLE  Threadhdl;
//DWORD   threadid;
class Semaphore
{
public:
	Semaphore();
	~Semaphore();
////////////////////////////////////////////////////////////////////////////////////////////////////
//Create a method that will process the semaphore
////////////////////////////////////////////////////////////////////////////////////////////////////
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
////////////////////////////////////////////////////////////////////////////////////////////////////
//This Method will create the semaphore that will create the object using the ThreadProc method seen above
////////////////////////////////////////////////////////////////////////////////////////////////////
	static int Semaphoremain();
};

