#include  "RevLab.h"
#include <string>

//-----------------------------------------------------------------------------
//					           		Reversi
//								   ---------
//
// General : The program simulates the game Reversi.
//
// Input   : One of 3 options: 1.new game 2.Load game 3.exit .
//		     in case of game loading, file name would be required.
//
// Process : Starts a new game or loads an existing game and run it.
//
// Output  : Prints the matrix game in every trunand eventually prints who
//			 is the winner. in case of game saving ,New file associated
//			 with this particular game will be created.
//
//-----------------------------------------------------------------------------
// Programmer : Nehoray Zvulun
// Student No : 205602634
// Date : 11.02.2015
//-----------------------------------------------------------------------------
int main()
{
	// Variables definition
	GameMat gmGameBoard;
	SquareState	sqrsCurrentTurn;
	int			nWhiteNoMoves;
	int			nBlackNoMoves;
	int			nMatrixRow;
	int			nMatrixCol;
	int			nMenuChoice;
	int			nErrorCode;
	bool		bIsMoveExist;
	bool		bIsAnswerCorrect;
	char		arrcFileName[50];
	char		cAnswerTav;
	
	// Code Section

	gmGameBoard.ShowMenu();

	// Get the user choice
	cin >> nMenuChoice;
	system("cls");

	// The game runs until the user asks to exit
	while (true)
	{
		switch (nMenuChoice)
		{
			// New game
			case (1):
			{
				gmGameBoard.ShowMatrix();
				while (true)
				{
					// flags to say if players has not any move to make
					nWhiteNoMoves = 0;
					nBlackNoMoves = 0;
					if (gmGameBoard.GetsqrsGameTurn() == WHITE)
					{
						cout << "White turn" << endl;
					}
					else
					{
						cout << "Black turn" << endl;
					}
						
					//Get row and Column form the user
					cout << "enter row : ";
					cin >> nMatrixRow;

					// if the user want to exit
					if (nMatrixRow == -999)
					{
						cout << "Would you like to save your game ? (y/n) -small letters-" << endl;
						cin >> cAnswerTav;
						
						// While the char the user gave is not 'y' or 'n' ,wait for 'y' or 'n' char
						bIsAnswerCorrect = false;
						while (!bIsAnswerCorrect)
						{
							// if the user doesnot want to save the game
							if (cAnswerTav == 'n')
							{
								bIsAnswerCorrect = true;

								return (1);
							}

							//if the user want to save the game
							else if (cAnswerTav == 'y')
							{
								//ask for a file name to save the game into it
								bIsAnswerCorrect = true;
								cout << "Enter the file name " << endl;
								cin >> arrcFileName;
								gmGameBoard.SaveGame(arrcFileName);
								cout << "game " << arrcFileName << " saved!" << endl;
								cout << "Press any key to exit..." << endl;
								_getch();
								return (1);
							}
						}
					}

					cout << "enter col : ";
					cin >> nMatrixCol;
					nErrorCode = gmGameBoard.CheckChoise(nMatrixRow, 9 - nMatrixCol);

					//if the move was leagl it was made alreay
					if (nErrorCode == 1)
					{
						system("cls");
						gmGameBoard.ShowMatrix();

						// keep the current player (A) in a virable 
						sqrsCurrentTurn = gmGameBoard.GetsqrsGameTurn();
						
						// let the other player (B) the trun
						gmGameBoard.SetsqrsGameTurn(gmGameBoard.GetOpponentState());
						bIsMoveExist = gmGameBoard.DoesMoveExist();

						// if the other player (B) has no legal moves to make
						if (!bIsMoveExist)
						{
							// Turn on the appropriate flags according to the player who has no moves
							if (gmGameBoard.GetOpponentState() == BLACK)
							{
								nWhiteNoMoves = 1;
							}
							else
							{
								nBlackNoMoves = 1;
							}

							// The previous player (A) will get one more turn
							gmGameBoard.SetsqrsGameTurn(sqrsCurrentTurn);

							// Check if the previous player (A) has legal moves
							bIsMoveExist = gmGameBoard.DoesMoveExist();

							// if he (A) has'nt trun the second falg on
							if (!bIsMoveExist)
							{
								if (gmGameBoard.GetOpponentState() == BLACK)
								{
									nWhiteNoMoves = 1;
								}
								else
								{
									nBlackNoMoves = 1;
								}
							}

							// If both players has no moves, the game must end
							if (nWhiteNoMoves && nBlackNoMoves)
							{
								// if the game stoped in the middle 
								if (gmGameBoard.GetNumOfNotOccupied() != 0)
								{
									cout << "There are no more moves to each player" << endl;
								}

								//end the game
								gmGameBoard.GameOver();
								nMenuChoice = 4;

								break;
							}

							// if its not the end but some one has no moves
							else if (nWhiteNoMoves && !nBlackNoMoves)
							{
								cout << "White player has no moves , Black player gets one more turn" << endl;
							}
							else if (!nWhiteNoMoves && nBlackNoMoves)
							{
								cout << "Black player has no moves , White player gets one more turn" << endl;
							}
						}
					}

					// If the move was ilegal print an appropriate messege
					else
					{
						system("cls");
						gmGameBoard.ShowMatrix();
						switch (nErrorCode)
						{
							// If the choice is out of matrix limits
							case (2) :
							{
								cout << "Wrong spot! - ";
								cout << "you have exceeded the bounds of the board game, plaese try again" << endl;

								break;
							}

							// if the chosen point is already taken
							case (3) :
							{
								cout << "Wrong spot! - ";
								cout << "The chosen point is already taken, plaese try again" << endl;

								break;
							}

							// Default error
							default:
							{
								cout << "Wrong spot! - ";
								cout << "The chosen spot is illegal, plaese try again" << endl;

								break;
							}
						}
					}
				}

				break;
			}

			// loading game
			case (2):
			{
				cout << "enter the file name " << endl;
				cin >> arrcFileName;
				system("cls");
				gmGameBoard.LoadGame(arrcFileName);

				// In order to run the game in case 1
				nMenuChoice = 1;

				break;
			}

			// exit
			case (3):
			{
				exit(1);

				break;
			}

			// in the end of the game the user will be tranfer to case 4 for menu 
			case (4):
			{
				system("cls");
				gmGameBoard.InitForStart();
				gmGameBoard.ShowMenu();
				cin >> nMenuChoice;
				system("cls");

				break;
			}

			// In any other case, the menu will be presented again until a legal choice had made
			default:
			{
				system("cls");
				gmGameBoard.ShowMenu();
				cin >> nMenuChoice;
				system("cls");

				break;
			}
		}
	}

	return (1);
}