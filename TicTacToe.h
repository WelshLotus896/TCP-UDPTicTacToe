#pragma once
#include "stdafx.h"
#include "UDPClient.h"
#define BOARD_WIDTH  3
#define BOARD_HEIGHT 3
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512


class TicTacToe
{
public:

	struct Player
	{
		int X;
		int Y;
		char player;

	}player;
	Player myPlayer;
	int X;
	int Y;
	int TOTAL_MOVES = 0;
	int X_MOVES = 0;
	int O_MOVES = 0;
	int playerTurn;
	char player2 = 'O';

	char board[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int d; //keyboard input
	WSADATA	wsaData;

	//char sendbuff[1000];
	int		iResult;


	char	recvbuf[DEFAULT_BUFLEN];

	int		recvbuflen = DEFAULT_BUFLEN;

	struct addrinfo *addressList = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;
	SOCKET UDPServer = INVALID_SOCKET;
	char* serverName = "127.0.0.1";

	char* sendbuf[100];
	char* updateBuffer[100];
public:
	TicTacToe();
	~TicTacToe();

	//Create the board
	void initBoard();

	//Print the instructions
	void instruction(void);
	//Switch Between players
	void TogglePlayer();
	//Check Win
	char checkWin();
	//Input
	void Input();
	//Game Loop
	void GameLoop();
	//Get the current X position of the player
	int GetPlayerX(void);
	//Get the current Y position of the player
	int GetPlayerY(void);
	//Set the current X position of the player
	int SetPlayerX(int x);
	//Set the current X position of the player
	int SetPlayerY(int y);
	//Update the board
	void updateBoard();
	char lastMove();
};