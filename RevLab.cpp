#define _CRT_SECURE_NO_DEPRECATE
#include  "RevLab.h"

//-----------------------------------------------------------------------------
//									 Square
//								    ---------
//
// General		: The function is a default constructor of the class Square.
//				  The function creates a new "NOT_OCCUPIED" Square object
//
// Parameters   : None
//
// Return Value : None
//
//-----------------------------------------------------------------------------
Square :: Square()
{
	this->SetSquareState(NOT_OCCUPIED);
}

//-----------------------------------------------------------------------------
//									 Get Square State
//									-----------------
//
// General		: The function returns the state of the current square.
//
// Parameters   : None
//
// Return Value : The state.
//
//-----------------------------------------------------------------------------
SquareState Square :: GetSquareState()
{
	return (this->sqrsSquareState);
}

//-----------------------------------------------------------------------------
//									 Set Square State
//									-----------------
//
// General		: The function put a new state in the square
//
// Parameters   : The state
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void Square :: SetSquareState(SquareState iState)
{
	this->sqrsSquareState = iState;
}

//-----------------------------------------------------------------------------
//									 operator <<
//									-------------
//
// General		: The function overloading the operator << for a square object
//
// Parameters   : 
//		Os	- Ostream object in order to return output (out)
//		sqr	- The object of the Square (in)
//
// Return Value : 
//
//-----------------------------------------------------------------------------
ostream& operator<< (ostream& oOutPut, const Square& isqrGameSquare)
{
	// Matches output letter to square state
	if (isqrGameSquare.sqrsSquareState == BLACK)
	{
		oOutPut << " B |";
	}
	if (isqrGameSquare.sqrsSquareState == WHITE)
	{
		oOutPut << " W |";
	}
	if (isqrGameSquare.sqrsSquareState == NOT_OCCUPIED)
	{
		oOutPut << "   |";
	}
	if (isqrGameSquare.sqrsSquareState == SAFE_WALL)
	{
		oOutPut << "|s|";
	}

	return oOutPut;
}

//-----------------------------------------------------------------------------
//									 GameMat
//								 ---------------
//
// General		: The function is a constructor for the GameMat class.
//				  the function is called when GameMat objects are created 
//
// Parameters   : None
//
// Return Value : None
//
//-----------------------------------------------------------------------------
GameMat :: GameMat()
{
	// Variable definition
	int nIndex;

	// Code Section

	// Initializes the Game variables for a new game
	this->sqrsGameTurn = WHITE;
	this->nBlackCounter = 0;
	this->nWhiteCounter = 0;
	this->nNotOccupiedCounter = 4;

	// Run on the edges and places safe wall
	for (nIndex = 0; nIndex < GAME_MAT_SIZE + 2; nIndex++)
	{
		this->arrsqrGameMat[0][nIndex].SetSquareState(SAFE_WALL);
		this->arrsqrGameMat[nIndex][0].SetSquareState(SAFE_WALL);
		this->arrsqrGameMat[nIndex][GAME_MAT_SIZE + 1].SetSquareState(SAFE_WALL);
		this->arrsqrGameMat[GAME_MAT_SIZE + 1][nIndex].SetSquareState(SAFE_WALL);
	}

	// Initializes the squares of the players to the initial state
	this->arrsqrGameMat[4][4].SetSquareState(BLACK);
	this->arrsqrGameMat[5][5].SetSquareState(BLACK);
	this->arrsqrGameMat[4][5].SetSquareState(WHITE);
	this->arrsqrGameMat[5][4].SetSquareState(WHITE);
}

//-----------------------------------------------------------------------------
//								 	Get Game Turn
//								  ------------------
//
// General		: The function returns the current turn
//
// Parameters   : None
//
// Return Value : The turn
//
//-----------------------------------------------------------------------------
SquareState GameMat :: GetsqrsGameTurn()
{
	return (this->sqrsGameTurn);
}

//-----------------------------------------------------------------------------
//								 	Set Game Turn
//								  -----------------
//
// General		: The function change the current turn to the given turn
//
// Parameters   : The new turn
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: SetsqrsGameTurn(SquareState isqrsNewturn)
{
	this->sqrsGameTurn = isqrsNewturn;
}

//-----------------------------------------------------------------------------
//									Get Opponent State
//									------------------
//
// General		: The function returns the opponent state
//
// Parameters   : None
//
// Return Value : The state of the opponent.
//
//-----------------------------------------------------------------------------
SquareState GameMat :: GetOpponentState()
{
	// Code Section

	if (sqrsGameTurn == WHITE)
		sqrsOpponentState = BLACK;
	else
		sqrsOpponentState = WHITE;

	return (sqrsOpponentState);
}

//-----------------------------------------------------------------------------
//									 Init For Start
//									----------------
//
// General		: The function initializes the Game to initial state
//				  the function is called when the user wants to play again
//
// Parameters   : None
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: InitForStart()
{
	// Variables definition
	int nMatrixRow;
	int nMatrixCol;
	//int nIndex;

	// Code Section

	// Initializes the Game variables for a new game
	this->sqrsGameTurn = WHITE;
	this->nBlackCounter = 0;
	this->nWhiteCounter = 0;
	this->nNotOccupiedCounter = 4;

	// places empty squares all over the matrix
	for (nMatrixRow = 1; nMatrixRow < GAME_MAT_SIZE + 1; nMatrixRow++)
	{
		for (nMatrixCol = 1; nMatrixCol < GAME_MAT_SIZE + 1; nMatrixCol++)
		{
			arrsqrGameMat[nMatrixRow][nMatrixCol].SetSquareState(NOT_OCCUPIED);
		}
	}
	
	// Initializes the squares of the players to the initial state
	arrsqrGameMat[4][4].SetSquareState(BLACK);
	arrsqrGameMat[5][5].SetSquareState(BLACK);
	arrsqrGameMat[4][5].SetSquareState(WHITE);
	arrsqrGameMat[5][4].SetSquareState(WHITE);
}

//-----------------------------------------------------------------------------
//									 Check Choise
//									--------------
//
// General		: The function Check if the point that the player chose
//				  is leagl, if it is, its checks for a bridge.
//
// Parameters   : 
//		inMatrixRow - row number of the point
//		inMatrixCol - column number of the point
//
// Return Value : check result code - (1) good choice (2) point is out
//				  of the matrix scope (3) point is already taken
//				  (0) all the rest
//
//-----------------------------------------------------------------------------
int GameMat :: CheckChoise(int inMatrixRow, int inMatrixCol)
{
	// Variables definition
	bool	bisMoveValid = false;
	int		nIndexVector;

	// Code Section

	this->sqrsOpponentState = GetOpponentState();
	
	// if the Chosen point is out of the matrix game
	if ( inMatrixRow < 1 || inMatrixRow > GAME_MAT_SIZE || 
		inMatrixCol < 1 || inMatrixCol > GAME_MAT_SIZE )
	{
		return (2);
	}

	// if the chosen point is already taken
	if (this->arrsqrGameMat[inMatrixRow][inMatrixCol].GetSquareState() != NOT_OCCUPIED)
	{
		return (3);
	}

	// if the function CheckMyNearSquares says the point is illegal
	if (this->CheckMyNearSquares(inMatrixRow, inMatrixCol) == false)
	{
		return (0);
	}

	// Running through all 8 squares around the cuurent squares and looking for a bridge
	for (nIndexVector = 0; nIndexVector < 8; nIndexVector++)
	{	
		// if one of squares around the cuurent squares is occupied by opponent
		if (this->arrsqrGameMat[inMatrixRow + INDEX_VECTOR[nIndexVector][0]][inMatrixCol +
			INDEX_VECTOR[nIndexVector][1]].GetSquareState() == sqrsOpponentState)
		{
			// Checks for a Bridge in the direction symbolized by 'nIndexVector'
			if (CheckBridge(inMatrixRow + INDEX_VECTOR[nIndexVector][0] * 2,
				inMatrixCol + INDEX_VECTOR[nIndexVector][1] * 2, nIndexVector))
			{
				// paint the bridge that the player just found
				this->arrsqrGameMat[inMatrixRow][inMatrixCol].SetSquareState(sqrsGameTurn);
				PaintBridge(inMatrixRow + INDEX_VECTOR[nIndexVector][0],
					inMatrixCol + INDEX_VECTOR[nIndexVector][1], nIndexVector);
				bisMoveValid = true;
			}
		}
	}
	if (!bisMoveValid)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

//-----------------------------------------------------------------------------
//									 Show Matrix
//									-------------
//
// General		: The function prints the matrix game for the user perspective
//
// Parameters   : None
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: ShowMatrix()
{
	// Variables definition
	int nMatrixRow;
	int nMatrixCol;

	// Code Section

	// running through the 'GAME_MAT_SIZE' for printing the numbers above
	for (nMatrixCol = GAME_MAT_SIZE; nMatrixCol > 0; nMatrixCol--)
	{
		cout << "  " << nMatrixCol << " ";
	}
	cout << endl<< " -------------------------------";
	cout << endl;

	// running through the matrix and print it.
	for (nMatrixRow = 1; nMatrixRow < GAME_MAT_SIZE + 1; nMatrixRow++)
	{
		cout << "|";
		for (nMatrixCol = 1; nMatrixCol < GAME_MAT_SIZE + 1; nMatrixCol++)
		{
			cout << arrsqrGameMat[nMatrixRow][nMatrixCol];
		}
		// print the numbers at the side of the matrix.
		cout << " " << nMatrixRow << endl;
		cout << " -------------------------------" << endl;;
	}
}

//-----------------------------------------------------------------------------
//									 Check Bridge
//									--------------
//
// General		: The function checks Recursively a giving direction for
//				  a bridge at the giving point.
//
// Parameters   : 
//		inMatrixRow		- row number of the point
//		inMatrixCol		- column number of the point
//		inIndexVector	- direction to be checked
//
// Return Value : (1) if there is a brige, else (0)
//
//-----------------------------------------------------------------------------
int GameMat :: CheckBridge(int inMatrixRow, int inMatrixCol, int inIndexVector)
{
	// Code Section

	// stopping condition - if Eventually we found a square of the cuurent player,
	// a bridge was found
	if (this->arrsqrGameMat[inMatrixRow][inMatrixCol].GetSquareState() == sqrsGameTurn)
	{
		return (1);
	}

	// If we reached to a SAFE WALL square or to NOT OCCUPIED square
	// - its not a bridge
	else if (this->arrsqrGameMat[inMatrixRow][inMatrixCol].GetSquareState() == SAFE_WALL ||
		this->arrsqrGameMat[inMatrixRow][inMatrixCol].GetSquareState() == NOT_OCCUPIED)
	{
		return (0);
	}

	// keep looking for the cuurent player square at the same direction.
	return (CheckBridge(inMatrixRow + INDEX_VECTOR[inIndexVector][0],
		inMatrixCol + INDEX_VECTOR[inIndexVector][1], inIndexVector));
}

//-----------------------------------------------------------------------------
//									 Paint Bridge
//									-------------
//
// General		: The function paints Recursively a bridge that discoverd
//				  Earlier
//				  
//
// Parameters   : 
//		inMatrixRow		- Row number of the point
//		inMatrixCol		- Column number of the point
//		inIndexVector	- Bridge direction  
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: PaintBridge(int inMatrixRow, int inMatrixCol, int inIndexVector)
{
	// Code Section

	// stopping condition - keep painting  as long as we get to an opponent squares
	if (this->arrsqrGameMat[inMatrixRow][inMatrixCol].GetSquareState() != sqrsGameTurn)
	{
		// paint the cuurent square
		this->arrsqrGameMat[inMatrixRow][inMatrixCol].SetSquareState(sqrsGameTurn);

		// send the next square in same direction to the function.
		PaintBridge(inMatrixRow + INDEX_VECTOR[inIndexVector][0],
			inMatrixCol + INDEX_VECTOR[inIndexVector][1], inIndexVector);
	}
}

//-----------------------------------------------------------------------------
//									Check My Near Squares
//									---------------------
//
// General		: The function checks the near 8 squres for any reason
//				   to Invalidate this point from being leagl
//
// Parameters   : 
//		inMatrixRow		- Row number of the point
//		inMatrixCol		- Column number of the point 
//
// Return Value : The answer about the point
//
//-----------------------------------------------------------------------------
bool GameMat :: CheckMyNearSquares(int inMatrixRow, int inMatrixCol)
{
	// Variables definition
	bool	bisMoveValid = true;
	int		nIndexVector;

	// Code Section

	sqrsOpponentState = GetOpponentState();
	
	// Running through the 8 near squres looking for one legal direction.
	for (nIndexVector = 0; nIndexVector < 8; nIndexVector++)
	{ 
		bisMoveValid = true;

		// if at this direction there is a squre of the current player,
		// no chance for a brige.
		if (this->arrsqrGameMat[inMatrixRow + INDEX_VECTOR[nIndexVector][0]]
			[inMatrixCol + INDEX_VECTOR[nIndexVector][1]].GetSquareState() == sqrsGameTurn)
		{
			bisMoveValid = false;
		}

		// if at this direction there is a squre of the safe wall, no chance for a brige.
		if (this->arrsqrGameMat[inMatrixRow + INDEX_VECTOR[nIndexVector][0]]
			[inMatrixCol + INDEX_VECTOR[nIndexVector][1]].GetSquareState() == SAFE_WALL)
		{
			bisMoveValid = false;
		}

		// if the current squre is safe wall, no chance for a brige.
		if (this->arrsqrGameMat[inMatrixRow][inMatrixCol].GetSquareState() == SAFE_WALL)
		{
			bisMoveValid = false;
		}

		// if at this direction there is'nt a squre of the opponent, no chance for a brige.
		if (arrsqrGameMat[inMatrixRow + INDEX_VECTOR[nIndexVector][0]]
			[inMatrixCol + INDEX_VECTOR[nIndexVector][1]].GetSquareState() != sqrsOpponentState)
		{
			bisMoveValid = false;
		}

		// if one of 8 squres is valid , the giving squre is ok
		if (bisMoveValid)
		{
			break;
		}
	}

	return (bisMoveValid);

}

//-----------------------------------------------------------------------------
//									Does Move Exist
//									---------------
//
// General		: The function checks if the cuurent player has atleast one 
//				  legal move
//
// Parameters   : None
//
// Return Value : The answer.
//
//-----------------------------------------------------------------------------
bool  GameMat :: DoesMoveExist()
{
	// Variables definition
	bool	bisMoveExist = true;
	int		nMatrixRow;
	int		nMatrixCol;
	int		nIndexVector;

	// Code Section

	sqrsOpponentState = GetOpponentState();

	// Running through the matrix looking for one legal move
	for (nMatrixRow = 1; nMatrixRow < GAME_MAT_SIZE + 1; nMatrixRow++)
	{
		for (nMatrixCol = 1; nMatrixCol < GAME_MAT_SIZE + 1; nMatrixCol++)
		{
			// if the square 'OCCUPIED' ,its can not be a legal move.
			if (this->arrsqrGameMat[nMatrixRow][nMatrixCol].GetSquareState() != NOT_OCCUPIED)
			{
				bisMoveExist = false;
			} 

			// if there is'nt one square around the cuurent squares that allows to keep testing
			if (this->CheckMyNearSquares(nMatrixRow, nMatrixCol) != true)
			{
				bisMoveExist = false;
			}

			// if the point did'nt Disqualified so far
			if (bisMoveExist)
			{		
				for (nIndexVector = 0;
					 nIndexVector < 8;
					 nIndexVector++)
				{
					// if in one of the diraction ,there is an opponent square
					if (arrsqrGameMat[nMatrixRow + INDEX_VECTOR[nIndexVector][0]]
						[nMatrixCol + INDEX_VECTOR[nIndexVector][1]].GetSquareState() == sqrsOpponentState)
					{
						// check for bridge in that diraction
						if (CheckBridge(nMatrixRow + INDEX_VECTOR[nIndexVector][0] * 2,
							nMatrixCol + INDEX_VECTOR[nIndexVector][1] * 2, nIndexVector))
						{
							return (true);
						}
					}
				}
			}
			
			// if the current square is not legal, we want to assume the next square is good before texting.
			else
			{
				bisMoveExist = true;
			}
		}
	}

	return (false);
}

//-----------------------------------------------------------------------------
//									Game Over
//									---------
//
// General		: The function called in the end of the game .
//				  it count the squares and Announces the winner or a draw
//
// Parameters   : None
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: GameOver()
{
	// Variables definition
	int nMatrixRow;
	int nMatrixCol;

	// Code Section

	//Running through the matrix and count how many squares has each player 
	for (nMatrixRow = 1; nMatrixRow < GAME_MAT_SIZE + 1; nMatrixRow++)
	{
		for (nMatrixCol = 1; nMatrixCol < GAME_MAT_SIZE + 1; nMatrixCol++)
		{
			if (arrsqrGameMat[nMatrixRow][nMatrixCol].GetSquareState() == BLACK)
			{
				nBlackCounter++;
			}
			else if (arrsqrGameMat[nMatrixRow][nMatrixCol].GetSquareState() == WHITE)
			{
				nWhiteCounter++;
			}
			else if (arrsqrGameMat[nMatrixRow][nMatrixCol].GetSquareState() == NOT_OCCUPIED)
			{
				nNotOccupiedCounter++;
			}
		}
	}
	// Print a message depending on the result
	if (nBlackCounter > nWhiteCounter)
	{
		cout << "Black won!!!" << endl;
	}
	else if (nWhiteCounter > nBlackCounter)
	{
		cout << "White won!!!" << endl;
	}
	else if (nWhiteCounter == nBlackCounter)
	{
		cout << "it's a Tie!" << endl;
	}
	cout << "Black : " << nBlackCounter << endl
		 << "White : " << nWhiteCounter << endl;
	cout << "GAME OVER : Press any key to continue..." << endl;
	_getch();
}

//-----------------------------------------------------------------------------
//									Get Num Of Not Occupied
//									-----------------------
//
// General		: The function counts how many empty squares are there
//				  and returns the count
//
// Parameters   : None
//
// Return Value : Number of empty squares
//
//-----------------------------------------------------------------------------
int GameMat :: GetNumOfNotOccupied()
{
	// Variables definition
	int nEmptySquareCounter = 0;
	int nMatrixRow;
	int nMatrixCol;

	// Code Section

	// Running through the matrix and count how many empty squarea are there
	for (nMatrixRow = 1; nMatrixRow < GAME_MAT_SIZE + 1; nMatrixRow++)
	{
		for (nMatrixCol = 1; nMatrixCol < GAME_MAT_SIZE + 1; nMatrixCol++)
		{
			if (arrsqrGameMat[nMatrixRow][nMatrixCol].GetSquareState() == NOT_OCCUPIED)
				nEmptySquareCounter++;
		}
	}

	return (nEmptySquareCounter);
}

//-----------------------------------------------------------------------------
//									Save Game
//							      -------------
//
// General		: The function saves the game into a file
//
// Parameters   : 
//		icFileName - file name
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: SaveGame(char* icFileName)
{
	// Variables definition
	SquareBuffer*	arrSquareToSave;
	FILE*			fFilePointer;
	int				nArraySize = ( 64 - GetNumOfNotOccupied() );
	int				nArrayIndex = 0;
	int				nMatrixRow;
	int				nMatrixCol;

	// Code Section

	arrSquareToSave = new SquareBuffer[nArraySize + 1];
	
	// The first cell is used in order to save the turn
	arrSquareToSave[nArrayIndex].row = -1;
	arrSquareToSave[nArrayIndex].col = -1;
	arrSquareToSave[nArrayIndex++].color = sqrsGameTurn;

	// Running through the matrix and loadig to an array every occupied square
	for (nMatrixRow = 1; nMatrixRow < GAME_MAT_SIZE + 1; nMatrixRow++)
	{
		for (nMatrixCol = 1; nMatrixCol < GAME_MAT_SIZE + 1; nMatrixCol++)
		{
			if (arrsqrGameMat[nMatrixRow][nMatrixCol].GetSquareState() != NOT_OCCUPIED)
			{
				arrSquareToSave[nArrayIndex].row = nMatrixRow;
				arrSquareToSave[nArrayIndex].col = nMatrixCol;
				arrSquareToSave[nArrayIndex++].color =
					arrsqrGameMat[nMatrixRow][nMatrixCol].GetSquareState();
			}
		}
	}
	nArraySize = nArrayIndex;

	// Writing the array to a file
	fFilePointer = fopen(icFileName, "wb");
	fwrite(arrSquareToSave, sizeof(struct SquareBuffer), nArraySize, fFilePointer);
	fclose(fFilePointer);
	delete []arrSquareToSave;
}

//-----------------------------------------------------------------------------
//									Load Game
//							      -------------
//
// General		: The function loads the game from a file
//
// Parameters   : 
//		icFileName - file name
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: LoadGame(char* icFileName)
{
	// Variable definition
	SquareBuffer	sqtsSquareBuffer;
	FILE*			fFilePointer;

	// Code Section

	// Try to open the file ,if it does not exist,recive new file name
	// and Verifying that such a file exists
	do
	{
		system("cls");
		fFilePointer = fopen(icFileName, "rb");

		// If the file exist, stop the do while because it can be read.
		if (fFilePointer != NULL)
		{
			break;
		}
		cout << "The enterd name does not exist ,please try again" << endl;
		cin >> icFileName;
	}
	while (fFilePointer == NULL);
	
	// Reading the first cell from the file which has the turn and place it in our game
	fread(&sqtsSquareBuffer, sizeof(struct SquareBuffer), 1, fFilePointer);
	this->sqrsGameTurn = sqtsSquareBuffer.color;// נציב התור

	// Reading the rest of the file and place the player's squares over the matrix
	while (!feof(fFilePointer))//כל עוד לא הגענו לסוף הקובץ
	{
		fread(&sqtsSquareBuffer, sizeof(struct SquareBuffer), 1, fFilePointer);
		this->arrsqrGameMat[sqtsSquareBuffer.row][sqtsSquareBuffer.col].SetSquareState(sqtsSquareBuffer.color);
	}
	fclose(fFilePointer);
}

//-----------------------------------------------------------------------------
//									Show Menu
//							      -------------
//
// General		: The function print the main menu
//
// Parameters   : None
//
// Return Value : None
//
//-----------------------------------------------------------------------------
void GameMat :: ShowMenu()
{
	cout << setw(201) << "~~~~~~~~~~~~~" << endl;
	cout << setw(198) << "Reversi" << endl;
	cout << setw(201) << "~~~~~~~~~~~~~" << endl;
	cout << setw(200) << "Main menu:" << endl;
	cout << setw(200) << "1.New game" << endl;
	cout << setw(201) << "2.Load game" << endl;
	cout << setw(196) << "3.exit" << endl;
}

