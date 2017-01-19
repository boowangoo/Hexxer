#include <SDL.h>
#include <iostream>
using namespace std;

#include "Game.h"
#include "Points.h"


Game::Game(){
	string nameMagenta, nameGreen, nameCyan;
	cout << "MAGENTA PLAYER, PLEASE ENTER YOUR NAME: ";
	cin >> nameMagenta;
	cout << "GREEN PLAYER, PLEASE ENTER YOUR NAME: ";
	cin >> nameGreen;
	cout << "CYAN PLAYER, PLEASE ENTER YOUR NAME: ";
	cin >> nameCyan;
	Points points(nameMagenta, nameGreen, nameCyan);

	SDL_Init(SDL_INIT_EVERYTHING);
	
	Graphics graphics((boardWidth + 0.5) * 50 + 25, boardHeight * 60 + 20);
	Board board(boardWidth, boardHeight);

	int selectedX = 0;
	int selectedY = 0;
	int preSelectedX = selectedX;
	int preSelectedY = selectedY;
	char* preImgPath = en;
	
	bool foundFirst = false;
	for (int i = 0; i < boardWidth && !foundFirst; i++) {
		if (board.tiles[i][0].GetState() != 'n') {	
			selectedX = i;
			foundFirst = true;
		}
	}

	while (true) {
		for (int i = 0; i < boardWidth; i++) {
			for (int j = 0; j < boardHeight; j++) {
				if(board.tiles[i][j].GetState() != 'n') {
					int xPos = board.tiles[i][j].GetX();
					int yPos = board.tiles[i][j].GetY();
					graphics.DrawTiles(board.tiles[i][j].GetImgPath(), 50, 60, xPos, yPos);
				}
			}
		}

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						if (selectedX - 1 >= 0 && board.tiles[selectedX - 1][selectedY].GetState() != 'n') {
							selectedX--;
						}
						break;
					case SDLK_RIGHT:
						if (selectedX + 1 < boardWidth && board.tiles[selectedX + 1][selectedY].GetState() != 'n') {
							selectedX++;
						}
						break;
					case SDLK_UP:
						if (selectedY - 1 >= 0 && board.tiles[selectedX][selectedY - 1].GetState() != 'n') {
							selectedY--;
						}
						break;
					case SDLK_DOWN:
						if (selectedY + 1 < boardHeight && board.tiles[selectedX][selectedY + 1].GetState() != 'n') {
							selectedY++;
						}
						break;
					case SDLK_SPACE:
						if (board.tiles[selectedX][selectedY].GetControl() == 'n') {
							board.tiles[selectedX][selectedY].SetState('c');							
							board.tiles[selectedX][selectedY].SetControl(currentControl);			
							if (board.FullBoard()) {
								event.type = SDL_QUIT;
							}
							if (board.Chain(selectedX, selectedY, 'c') >= 3) {
								board.tiles[selectedX][selectedY].SetState('u');
								board.tiles[selectedX][selectedY].SetImgPath(currentUltra);
								points.AddPoints('u', currentControl);
								cout << nameMagenta << "'s points: " << points.GetPoints('m') << endl;
								cout << nameGreen << "'s points: " << points.GetPoints('g') << endl;
								cout << nameCyan << "'s points: " << points.GetPoints('c') << endl << endl;
								preImgPath = currentUltra;
								board.Clear(selectedX, selectedY);
							}
							else {
								board.tiles[selectedX][selectedY].SetImgPath(currentClaimed);
								preImgPath = currentClaimed;
								points.AddPoints('c', currentControl);
								cout << nameMagenta << "'s points: " << points.GetPoints('m') << endl;
								cout << nameGreen << "'s points: " << points.GetPoints('g') << endl;
								cout << nameCyan << "'s points: " << points.GetPoints('c') << endl << endl;
							}
							ColourSwitch(currentControl);
							
						}
						//board.StatePrint();
						break;
				}
				if (!(preSelectedX == selectedX && preSelectedY == selectedY)) {
					char* newImgPath = board.tiles[selectedX][selectedY].GetImgPath();
					board.tiles[selectedX][selectedY].SetImgPath(currentSelected);
					board.tiles[preSelectedX][preSelectedY].SetImgPath(preImgPath);
					preSelectedX = selectedX;
					preSelectedY = selectedY;
					preImgPath = newImgPath;
				}
			}
			if (event.type == SDL_QUIT) {
				IMG_Quit();
				cout << nameMagenta << "'s points: " << points.GetPoints('m') << endl;
				cout << nameGreen << "'s points: " << points.GetPoints('g') << endl;
				cout << nameCyan << "'s points: " << points.GetPoints('c') << endl << endl;
				points.CopyInfo(nameMagenta, nameGreen, nameCyan, points.GetPoints('m'), points.GetPoints('g'), points.GetPoints('c'));
				points.PasteInfo();
				points.ResetPoints();
				return;
			}
		}
		SDL_Delay(20);
	}
}

Game::~Game(){
}

void Game::ColourSwitch(char currentColour) {
	switch (currentColour) {
		case 'm':
			//turns from m to g
			//cout << "m to g" << endl;
			currentControl = 'g';
			currentSelected = sg;
			currentClaimed = cg;
			currentUltra = ug;
			break;
		case 'g':
			//turns from g to c
			//cout << "g to c" << endl;
			currentControl = 'c';
			currentSelected = sc;
			currentClaimed = cc;
			currentUltra = uc;
			break;
		case 'c':
			//turns from c to m
			//cout << "c to m" << endl;
			currentControl = 'm';
			currentSelected = sm;
			currentClaimed = cm;
			currentUltra = um;
			break;
	}
}