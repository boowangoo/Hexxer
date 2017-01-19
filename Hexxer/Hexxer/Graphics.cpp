#include "Graphics.h"
#include "stdio.h"

Graphics::Graphics(int width, int height){ 
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Hexxer");
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Sets the background colour
	SDL_RenderClear(renderer); //As the background is figure graphic to be declared, everything before it is cleared
}

Graphics::~Graphics(){ // Destructor
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Graphics::DrawTiles(char* imgPath, int width, int height, int xPos, int yPos) {
	SDL_Rect newRect;
	newRect.h = height;
	newRect.w = width;
	newRect.x = xPos;
	newRect.y = yPos;

	SDL_Surface *bitmap = IMG_Load(imgPath);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bitmap);
	SDL_RenderCopy(renderer, texture, NULL, &newRect); //Texture is drawn on renderer
	SDL_RenderPresent(renderer); //Screen is updated

	SDL_FreeSurface(bitmap);
	SDL_DestroyTexture(texture);//gets rid of pointers
}