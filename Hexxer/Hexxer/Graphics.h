#include <SDL.h>
#include <SDL_image.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics{
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	Graphics(int, int);
	~Graphics();
	void DrawTiles(char* imgPath, int, int, int, int);
};

#endif