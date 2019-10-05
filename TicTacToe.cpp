#include "stdafx.h"
#include "TicTacToe.h"


TicTacToe::TicTacToe()
{

}


TicTacToe::~TicTacToe()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to initialise board
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::initBoard()
{
	//system("CLS");
	updateBoard();
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	//lastMove();
	
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to check if one of the players has won
////////////////////////////////////////////////////////////////////////////////////////////////////
char TicTacToe::checkWin()
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////Check if Player One Wins
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Check Across
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
	{
		return 'X';
	}

	if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
	{
		return 'X';
	}

	if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
	{
		return 'X';
	}


	///////////////////////////////////////////////////////////////////////////////////////
	//////Down
	///////////////////////////////////////////////////////////////////////////////////////
	if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
	{
		return 'X';
	}

	if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
	{
		return 'X';
	}

	if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
	{
		return 'X';
	}
	////////////////////////////////////////////////////////////////////////////////////////
	//////Diagonal
	////////////////////////////////////////////////////////////////////////////////////////
	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
	{
		return 'X';
	}

	if (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X')
	{
		return 'X';
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////check if Player 2 wins
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Check Across
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
	{
		return 'O';
	}

	if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
	{
		return 'O';
	}

	if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
	{
		return 'O';
	}


	///////////////////////////////////////////////////////////////////////////////////////
	//////Down
	///////////////////////////////////////////////////////////////////////////////////////
	if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
	{
		return 'O';
	}

	if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
	{
		return 'O';
	}

	if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
	{
		return 'O';
	}
	////////////////////////////////////////////////////////////////////////////////////////
	//////Diagonal
	////////////////////////////////////////////////////////////////////////////////////////
	if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
	{
		return 'O';
	}

	if (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O')
	{
		return 'O';
	}

	return '/';
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to check whose turn it is
////////////////////////////////////////////////////////////////////////////////////////////////////
int TicTacToe::CheckTurn(int)
{
	if (playerTurn == 1)
	{
		playerTurn = 2;

	}
	else
	{
		playerTurn = 1;
	}
	return playerTurn;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to start the game loop which will be used in the semaphore
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::GameLoop()
{
	initBoard();

	for (int i = 0; i < 9; i++)
	{
		
		initBoard();

		if (checkWin() == 'X')
		{
			cout << "Player 1 wins!\n";
			break;

		}
		if (checkWin() == 'O')
		{
			cout << "Player 2 wins!\n";
			break;


		}
		

	}


	system("pause");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to update the board whenever a move has been made
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::updateBoard()
{
	//Check to see whos go is it
	if (playerTurn == 1)
	{
//Its player 1s go
		if (player.X == -1 && player.Y == 1)
		{
			board[0][0] = player.player1;
		}



		if (player.X == 0 && player.Y == 1)
		{
			board[0][1] = player.player1;
			//myUDP.SendUpdate2();
		}



		if (player.X == 1 && player.Y == 1)
		{
			board[0][2] = player.player1;
		}


		if (player.X == -1 && player.Y == 0)
		{
			board[1][0] = player.player1;


		}



		if (player.X == 0 && player.Y == 0)
		{
			board[1][1] = player.player1;


		}

		if (player.X == 1 && player.Y == 0)
		{
			board[1][2] = player.player1;


		}



		if (player.X == -1 && player.Y == -1)
		{
			//set the symbol
			board[2][0] = player.player1;


		}



		if (player.X == 0 && player.Y == -1)
		{
			board[2][1] = player.player1;


		}





		if (player.X == -1 && player.Y == 1)
		{
			board[2][2] = player.player1;

		}
	}
		
//
//////////////////////////////////////////////////////////////////
//////Player 2
//////////////////////////////////////////////////////////////////
	if(playerTurn == 2)
	{
	if (player.X == -1 && player.Y == 1)
	{
		board[0][0] = player.player2;
	}



	if (player.X == 0 && player.Y == 1)
	{
		board[0][1] = player.player2;
		//myUDP.SendUpdate2();
	}



	if (player.X == 1 && player.Y == 1)
	{
		board[0][2] = player.player2;
	}


	if (player.X == -1 && player.Y == 0)
	{
		board[1][0] = player.player2;
		
		
	}



	if (player.X == 0 && player.Y == 0)
	{
		board[1][1] = player.player2;
	
	
	}

	if (player.X == 1 && player.Y == 0)
	{
		board[1][2] = player.player2;
	

	}



	if (player.X == -1 && player.Y == -1)
	{
		//set the symbol
		board[2][0] = player.player2;


	}



	if (player.X == 0 && player.Y == -1)
	{
		board[2][1] = player.player2;


	}





	if (player.X == -1 && player.Y == 1)
	{
		board[2][2] = player.player2;

	}
  }
	
}
	

////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to set the player X
////////////////////////////////////////////////////////////////////////////////////////////////////
int TicTacToe::SetPlayerX(int x)
{
	player.X = x;
//printf("X: %d\n", player.X);
	
	return player.X;
	
}

int TicTacToe::SetPlayerY(int y)
{
	//Get the position sent from the client and have the player store it
	player.Y = y;
	//printf("Y: %d\n", player.Y);

	return player.Y;
}

int TicTacToe::SetPlayerTurn(int Turn)
{
	playerTurn = Turn;
	
	return playerTurn;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to get the last move that was made
////////////////////////////////////////////////////////////////////////////////////////////////////
char TicTacToe::lastMove()
{
	printf("Last Move made: X: %i , Y: %i\n", player.X, player.Y);
	if (player.X && player.Y == 'X')
	{
		printf("Player 1 Made the last move (X)\n");
	}

	if (player.X && player.Y == 'O')
	{
		printf("Player 2 Made the last move (0)\n");
	}
	return 0;
}

