#include "Board.h"



Board::Board(int width, int height) {
	boardHeight = height;
	boardWidth = width;

	tiles = new Tile*[width];
	for (int i = 0; i < width; i++) {
		tiles[i] = new Tile[height];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (j % 2 == 1) {
				if (j < height / 2) {
					if (i < ((height / 2) - j + 1) / 2
					|| i > width - ((height / 2) - j + 1) / 2) {
						tiles[i][j].SetState('n');
					}
				}
				else if (j > height / 2) {
					if (i < (j - (height / 2) + 1) / 2 
					|| i > width - (j - (height / 2) + 1) / 2) {
						tiles[i][j].SetState('n');
					}
				}
				tiles[i][j].SetX(50 * i);
				tiles[i][j].SetY(45 * j + 50);
			}
			else {
				if (j < height / 2) {
					if (i < ((height / 2) - j) / 2
					|| i > width - ((height / 2) - j) / 2 - 1) {
						tiles[i][j].SetState('n');
					}
				}
				else if (j > height / 2) {
					if (i < (j - (height / 2)) / 2
					|| i > width - (j - (height / 2)) / 2 - 1) {

						tiles[i][j].SetState('n');
					}
				}
				tiles[i][j].SetX(50 * (i + 0.5));
				tiles[i][j].SetY(45 * j + 50);
			}
		}
	}	
}


Board::~Board()
{
	delete tiles;
}

int Board::GetWidth() {
	return boardWidth;
}

int Board::GetHeight() {
	return boardHeight;
}


void Board::MoveSelected(int origX, int origY, int newX, int newY) {
	tiles[newX][newY] = tiles[origX][origY];
}
#include <iostream>
bool Board::FullBoard() {
	for (int i = 0; i < boardWidth; i++) {
		for (int j = 0; j < boardHeight; j++) {
			if (tiles[i][j].GetState() == 'e') {
				return false;
			}
		}
	}
	return true;
}

/*void Board::ResetBoard(){
	std::cout << "resetting board!" << std::endl;
	for (int i = 0; i < boardWidth; i++) {
		for (int j = 0; j < boardHeight; j++) {
			if (tiles[i][j].GetState() != 'n' && tiles[i][j].GetState() != 'u') {
				tiles[i][j].SetState('e');
				tiles[i][j].SetControl('n');
				tiles[i][j].SetImgPath("resources/tiles/empty_neutral.png");
			}
		}
	}
}*/
#include <iostream>

int Board::Chain(int tileX, int tileY, char tileState) {
	int chainLength = 1;
	tiles[tileX][tileY].SetState('a');
	if (tileX > 0
		&& tiles[tileX - 1][tileY].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX - 1][tileY].GetControl()) {
		chainLength += Chain(tileX - 1, tileY, tileState);
	}
	if (tileX < boardWidth - 1
		&& tiles[tileX + 1][tileY].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX + 1][tileY].GetControl()) {
		chainLength += Chain(tileX + 1, tileY, tileState);
	}
	if (tileY > 0
		&& tiles[tileX][tileY - 1].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX][tileY - 1].GetControl()) {
		chainLength += Chain(tileX, tileY - 1, tileState);
	}
	if (tileY < boardHeight - 1
		&& tiles[tileX][tileY + 1].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX][tileY + 1].GetControl()) {
		chainLength += Chain(tileX, tileY + 1, tileState);
	}
	if (tileX < boardWidth - 1 && tileY > 0 && tileY % 2 == 0
		&& tiles[tileX + 1][tileY - 1].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX + 1][tileY - 1].GetControl()) {
		chainLength += Chain(tileX + 1, tileY - 1, tileState);
	}
	if (tileX > 0 && tileY > 0 && tileY % 2 == 1
		&& tiles[tileX - 1][tileY - 1].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX - 1][tileY - 1].GetControl()) {
		chainLength += Chain(tileX - 1, tileY - 1, tileState);
	}
	if (tileX < boardWidth - 1 && tileY < boardHeight - 1 && tileY % 2 == 0
		&& tiles[tileX + 1][tileY + 1].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX + 1][tileY + 1].GetControl()) {
		chainLength += Chain(tileX + 1, tileY + 1, tileState);
	}
	if (tileX > 0 && tileY < boardHeight - 1 && tileY % 2 == 1
		&& tiles[tileX - 1][tileY + 1].GetState() == tileState
		&& tiles[tileX][tileY].GetControl() == tiles[tileX - 1][tileY + 1].GetControl()) {
		chainLength += Chain(tileX - 1, tileY + 1, tileState);
	}
	
	tiles[tileX][tileY].SetState(tileState);

	return chainLength;
}

void Board::Clear(int tileX, int tileY) {
	//std::cout << "clear pivot: " << tileX << tileY << std::endl;
	if (tileX > 0
		&& tiles[tileX - 1][tileY].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX - 1][tileY].GetControl()) {		
		tiles[tileX - 1][tileY].SetState('e');
		Clear(tileX - 1, tileY);
		tiles[tileX - 1][tileY].SetControl('n');
		tiles[tileX - 1][tileY].SetImgPath("resources/tiles/empty_neutral.png");
	}

	if (tileX < boardWidth - 1
		&& tiles[tileX + 1][tileY].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX + 1][tileY].GetControl()) {
		tiles[tileX + 1][tileY].SetState('e');
		Clear(tileX + 1, tileY);
		tiles[tileX + 1][tileY].SetControl('n');
		tiles[tileX + 1][tileY].SetImgPath("resources/tiles/empty_neutral.png");
	}

	if (tileY > 0
		&& tiles[tileX][tileY - 1].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX][tileY - 1].GetControl()) {
		tiles[tileX][tileY - 1].SetState('e');
		Clear(tileX, tileY - 1);
		tiles[tileX][tileY - 1].SetControl('n');
		tiles[tileX][tileY - 1].SetImgPath("resources/tiles/empty_neutral.png");
	}

	if (tileY < boardHeight - 1
		&& tiles[tileX][tileY + 1].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX][tileY + 1].GetControl()) {
		tiles[tileX][tileY + 1].SetState('e');
		Clear(tileX, tileY + 1);
		tiles[tileX][tileY + 1].SetControl('n');
		tiles[tileX][tileY + 1].SetImgPath("resources/tiles/empty_neutral.png");
	}

	if (tileX < boardWidth - 1 && tileY > 0 && tileY % 2 == 0
		&& tiles[tileX + 1][tileY - 1].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX + 1][tileY - 1].GetControl()) {
		tiles[tileX + 1][tileY - 1].SetState('e');
		Clear(tileX + 1, tileY - 1);
		tiles[tileX + 1][tileY - 1].SetControl('n');
		tiles[tileX + 1][tileY - 1].SetImgPath("resources/tiles/empty_neutral.png");
	}

	if (tileX > 0 && tileY > 0 && tileY % 2 == 1
		&& tiles[tileX - 1][tileY - 1].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX - 1][tileY - 1].GetControl()) {
		tiles[tileX - 1][tileY - 1].SetState('e');
		Clear(tileX - 1, tileY - 1);
		tiles[tileX - 1][tileY - 1].SetControl('n');
		tiles[tileX - 1][tileY - 1].SetImgPath("resources/tiles/empty_neutral.png");
	}

	if (tileX < boardWidth - 1 && tileY < boardHeight - 1 && tileY % 2 == 0
		&& tiles[tileX + 1][tileY + 1].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX + 1][tileY + 1].GetControl()) {
		tiles[tileX + 1][tileY + 1].SetState('e');
		Clear(tileX + 1, tileY + 1);
		tiles[tileX + 1][tileY + 1].SetControl('n');
		tiles[tileX + 1][tileY + 1].SetImgPath("resources/tiles/empty_neutral.png");
	}

	if (tileX > 0 && tileY < boardHeight - 1 && tileY % 2 == 1
		&& tiles[tileX - 1][tileY + 1].GetState() == 'c'
		&& tiles[tileX][tileY].GetControl() == tiles[tileX - 1][tileY + 1].GetControl()) {
		tiles[tileX - 1][tileY + 1].SetState('e');
		Clear(tileX - 1, tileY + 1);
		tiles[tileX - 1][tileY + 1].SetControl('n');
		tiles[tileX - 1][tileY + 1].SetImgPath("resources/tiles/empty_neutral.png");
	}
}

void Board::StatePrint() {
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			if (tiles[i][j].GetState() != 'n') {
				std::cout << tiles[i][j].GetState();
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}