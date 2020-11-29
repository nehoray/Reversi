#ifndef REVLAB_H
#define REVLAB_H
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <cstdlib> 
#include <iomanip>
using namespace std;
#define GAME_MAT_SIZE 8

// Enum definition
enum SquareState
{
	WHITE,
	BLACK,
	NOT_OCCUPIED,
	SAFE_WALL 
};

// struct definition
struct SquareBuffer
{
	int			row;
	int			col;
	SquareState color;
};

//Classes definition

// Square calss definition
class Square
{
private:
	 SquareState	sqrsSquareState;
public:

	 // Function Prototypes
	 Square();
	 SquareState		GetSquareState();
	 void				SetSquareState(SquareState	iState);
	 friend	ostream&	operator<< (ostream&	oOutPut, const Square&	isqrGameSquare);
};

// GameMat class definition
class GameMat
{
private:
	SquareState	sqrsGameTurn;
	SquareState	sqrsOpponentState;
	int			nWhiteCounter;
	int			nBlackCounter;
	int			nNotOccupiedCounter;
	Square		arrsqrGameMat[GAME_MAT_SIZE+2][GAME_MAT_SIZE+2];
public:

	// Function Prototypes
	GameMat();
	int			GetnNotOccupiedCounter();
	SquareState GetsqrsGameTurn();
	void		SetsqrsGameTurn(SquareState isqrsNewturn);
	SquareState	GetOpponentState();
	void		InitForStart();
	int			CheckChoise(int	inMatrixRow,
							int	inMatrixCol); 
	void		ShowMatrix();
	int			CheckBridge(int	inMatrixRow,
							int	inMatrixCol,
							int	inIndexVector);
	void		PaintBridge(int	inMatrixRow,
							int	inMatrixCol,
							int	inIndexVector);
	bool		CheckMyNearSquares(int	inMatrixRow,
								   int	inMatrixCol);
	bool		DoesMoveExist();
	void		GameOver();
	int			GetNumOfNotOccupied();
	void		SaveGame(char*	icFileName);
	void		LoadGame(char*	icFileName);
	void		ShowMenu();
};

const	int	INDEX_VECTOR[8][2] = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 },
									{ 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 } };
#endif