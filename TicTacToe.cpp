#include "stdafx.h"
#include "TicTacToe.h"


TicTacToe::TicTacToe()
{
	//used for second player 
	
	myPlayer.player = 'O';
}


TicTacToe::~TicTacToe()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to initialise board
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::initBoard()
{
	UDPClient myUDP;
	updateBoard();
	//system("CLS");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
		
		
	}
	
	
	cout << "Total Moves Made: " << TOTAL_MOVES << endl;
	cout << "\n";
	//cout << TOTAL_MOVES << endl;
	cout << "Total Moves Player 1 (X) Made: " << X_MOVES << endl;
	cout << "\n";
	//	cout << X_MOVES << endl;
	cout << "Total Moves Player 2 (O) Made: " << O_MOVES << endl;
	//	cout << O_MOVES << endl;
	
	cout << "*********************************************************\n" << endl;
	cout << "\n" << endl;
	//lastMove();
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to give instructions on how to play the game
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::instruction(void)
{
	printf("Player 1 has X, Player 2 has 0. Choose a cell shown below and play to win \n");
	printf("____________________________\n");
	printf("\n\n");
	printf("\t\t\t   1 |   2   |  3    \n", board[0][0], board[0][1], board[0][2]);
	printf("\t\t\t  ------------------\n");
	printf("\t\t\t   4 |   5   |  6    \n", board[1][0], board[1][1], board[1][2]);
	printf("\t\t\t  ------------------\n");
	printf("\t\t\t   7 |   8   |  9 \n\n", board[2][0], board[2][1], board[2][2]);


	printf("____________________________\n");


}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to toggle the players turn
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::TogglePlayer()
{
	if (playerTurn == 1)
	{
		playerTurn = 2;
		
	}
	else
	{
		playerTurn = 1;
	}
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
//This method is to recieve the input of the key when the player chooses a position on the board
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::Input()
{
	UDPClient myUDP;
	cin >> d;

	//check which fields have been selected 
	if (playerTurn == 2 && d == 1)
	{
		board[0][0] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		//send message to the server
		player.X = -1;
		player.Y = 1;
	
		
		}
	//board[player.X][player.Y] = player.player2;


	

	if (playerTurn == 2 && d == 2)
	{
		board[0][1] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		//send message to the server
		player.X = 0;
		player.Y = 1;
	}



	if (playerTurn == 2 && d == 3)
	{
		board[0][2] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		//send message to the server
		player.X = 1;
		player.Y = 1;
	}


	if (playerTurn == 2 && d == 4)
	{
		board[1][0] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		player.X = -1;
		player.Y = 0;
	}





	if (playerTurn == 2 && d == 5)
	{
		board[1][1] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		player.X = 0;
		player.Y = 0;
	}




	if (playerTurn == 2 && d == 6)
	{
		board[1][2] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		//send message to the server
		player.X = 1;
		player.Y = 0;
	}


	if (playerTurn == 2 && d == 7)
	{
		board[2][0] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		player.X = -1;
		player.Y = -1;
	}



	if (playerTurn == 2 && d == 8)
	{
		board[2][1] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		player.X = 0;
		player.Y = -1;
	
	}





	if (playerTurn == 2 && d == 9)
	{
		board[2][2] = player2;
		TOTAL_MOVES++;
		X_MOVES++;
		//send message to the server
		player.X = 1;
		player.Y = -1;
	}



}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to start the game loop which will be used in the semaphore
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::GameLoop()
{
	UDPClient myUDP;
	instruction();
	initBoard();
	
while(1)
{
		Input();
		initBoard();
		myUDP.SendPacking(player.X,player.Y);
		//Send the current board to the server
		
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
	
		TogglePlayer();

		
	}


	system("pause");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to get the X coordinate of the player
////////////////////////////////////////////////////////////////////////////////////////////////////
int TicTacToe::GetPlayerX(void)
{
	printf("X: %i", player.X);

	return player.X;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to get the Y coordinate of the player
////////////////////////////////////////////////////////////////////////////////////////////////////
int TicTacToe::GetPlayerY(void)
{
	printf("Y: %i", player.Y);

	return player.Y;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to Set the X coordinate of the player
////////////////////////////////////////////////////////////////////////////////////////////////////
int TicTacToe::SetPlayerX(int x)
{
	myPlayer.X = x;
	//printf("X: %d\n", player.X);

	return myPlayer.X;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to set the Y coordinate of the player
////////////////////////////////////////////////////////////////////////////////////////////////////
int TicTacToe::SetPlayerY(int y)
{
	//Get the position sent from the client and have the player store it
	myPlayer.Y = y;
	//printf("Y: %d\n", player.Y);

	return myPlayer.Y;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//This method is to update the board whenever a move has been made
////////////////////////////////////////////////////////////////////////////////////////////////////
void TicTacToe::updateBoard()
{
	//////////////////////////////////////////////////////////////////
//////Player 2
//////////////////////////////////////////////////////////////////
	if (myPlayer.X == -1 && myPlayer.Y == 1)
	{
		board[0][0] = myPlayer.player;
	}



	if (myPlayer.X == 0 && myPlayer.Y == 1)
	{
		board[0][1] = myPlayer.player;
		//myUDP.SendUpdate2();
	}



	if (myPlayer.X == 1 && myPlayer.Y == 1)
	{
		board[0][2] = myPlayer.player;
	}


	if (myPlayer.X == -1 && myPlayer.Y == 0)
	{
		board[1][0] = myPlayer.player;
		
		
	}



	if (myPlayer.X == 0 && myPlayer.Y == 0)
	{
		board[1][1] = myPlayer.player;
	
	
	}

	if (myPlayer.X == 1 && myPlayer.Y == 0)
	{
		board[1][2] = myPlayer.player;
	

	}



	if (myPlayer.X == -1 && myPlayer.Y == -1)
	{
		//set the symbol
		board[2][0] = myPlayer.player;


	}



	if (myPlayer.X == 0 && myPlayer.Y == -1)
	{
		board[2][1] = myPlayer.player;


	}





	if (myPlayer.X == -1 && myPlayer.Y == 1)
	{
		board[2][2] = myPlayer.player;

	}
}

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

