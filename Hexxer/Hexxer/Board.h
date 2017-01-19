#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

class Board
{
private:
	int boardWidth;
	int boardHeight;
public:
	Tile **tiles = 0;
	Board(int, int);
	~Board();

	int GetWidth();
	int GetHeight();

	void MoveSelected(int, int, int, int);
	bool FullBoard();
	int Chain(int, int, char);
	void Clear(int, int);
	void StatePrint();

};

#endif