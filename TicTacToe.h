#pragma once
#include "stdafx.h"
#define BOARD_WIDTH  3
#define BOARD_HEIGHT 3

class TicTacToe
{
private:

	struct Player
	{
		int X;
		int Y;
		char player1 = 'X';
		char player2 = 'O';
	}player;

	
	int playerTurn;
	char player1 = 'X';
	char player2 = 'O';
	char board[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	bool update = false;
public:
	TicTacToe();
	~TicTacToe();

	//Create the board
	void initBoard();
	//Check Win
	char checkWin();
	//Check whos turn it is
	int CheckTurn(int);
	//Game Loop
	void GameLoop();
	void updateBoard();
//	void SetChangePlayer2(char player2);
	int SetPlayerX(int x);
	int SetPlayerY(int y);
	int SetPlayerTurn(int playerTurn);
	char lastMove();
};