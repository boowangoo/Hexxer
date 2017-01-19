#ifndef GAME_H
#define GAME_H

#include "Graphics.h"
#include "Board.h"
class Graphics;

class Game{
private:
	SDL_Event event;

	int boardWidth = 9;
	int boardHeight = 9;

	char currentControl = 'm';
	char* currentSelected = "resources/tiles/selected_magenta.png";
	char* currentClaimed = "resources/tiles/claimed_magenta.png";
	char* currentUltra = "resources/tiles/ultra_magenta.png";

	char* sm = "resources/tiles/selected_magenta.png";
	char* cm = "resources/tiles/claimed_magenta.png";
	char* um = "resources/tiles/ultra_magenta.png";
	char* sg = "resources/tiles/selected_green.png";
	char* cg = "resources/tiles/claimed_green.png";
	char* ug = "resources/tiles/ultra_green.png";
	char* sc = "resources/tiles/selected_cyan.png";
	char* cc = "resources/tiles/claimed_cyan.png";
	char* uc = "resources/tiles/ultra_cyan.png";
	char* en = "resources/tiles/empty_neutral.png";

public:
	Game();
	~Game();
	void ColourSwitch(char);
};

#endif