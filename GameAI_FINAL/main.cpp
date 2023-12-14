#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 532;
const int SCREEN_HEIGHT = 513;

const std::string IMAGE_FILENAME = "Images/Image_47.bmp";

bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gImage = NULL;


SDL_Surface* loadSurface(std::string path) 
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) 
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else 
	{
		//convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL) 
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

bool loadMedia() 
{
	//Loading success flag
	bool success = true;

	gImage = SDL_LoadBMP("Images/Image_47.bmp");
	if (gImage == NULL) 
	{
		printf("Unable to load image! SDL_ERROR: %s\n", "Images/Image_47.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close() 
{
	//Deallocate surface
	SDL_FreeSurface(gImage);
	gImage = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
}

int main(int argc, char* args[])
{
	Game::createInstance();
	Game* p_game = Game::getInstance();
	if (!p_game->init(SCREEN_WIDTH, SCREEN_HEIGHT)) 
	{
		printf("Failed to initialize!\n");
	}
	else 
	{
		//load media
		if (!loadMedia()) 
		{
			printf("Failed to load media!\n");
		}
		else 
		{
			//Game Loop
			SDL_Event e; 
			bool quit = false; 
			while (quit == false) 
			{ 
				//poll events
				while (SDL_PollEvent(&e)) 
				{ 
					if (e.type == SDL_QUIT) 
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) 
					{
						switch (e.key.keysym.sym) 
						{
							case SDLK_UP:
								printf("up\n");
								break;
							case SDLK_DOWN:
								printf("down\n");
								break;
							case SDLK_LEFT:
								printf("left\n");
								break;
							case SDLK_RIGHT:
								printf("right\n");
								break;
							case SDLK_ESCAPE:
								quit = true;
								break;
						}
					}
				} 

				//Apply image
				SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
				//Update surface
				SDL_UpdateWindowSurface(p_game->getWindow());
			}
		}
	}

	close();
	delete p_game;
	return 0;
}
