#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include "Texture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 630;
const int SCREEN_HEIGHT = 480;

const std::string IMAGE_FILENAME = "Images/Image_47.bmp";
const std::string T_WALL_FILENAME = "Images/wall.png";
const std::string T_PATH_FILENAME = "";
const std::string TEST_IMG_FILENAME = "Images/cheeks.png";
const std::string TEST_FONT_FILENAME = "Fonts/Alice-Regular.ttf";

bool loadMedia();
void close();
void renderTextures();

SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gImage = NULL;

Texture test_image;
Texture test_ttf;
Texture wall_img;


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

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}

	if (!test_image.loadFromFile(TEST_IMG_FILENAME)) 
	{
		printf("Failed to load test image!\n");
		success = false;
	}

	if (!wall_img.loadFromFile(T_WALL_FILENAME)) 
	{
		printf("Failed to load wall image!\n");
		success = false;
	}

	if (TTF_Init() == -1) 
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	if (!(Game::getInstance()->setFont(TEST_FONT_FILENAME,28))) 
	{
		success = false;
	}
	else 
	{
		SDL_Color textColor = {255, 255, 255};
		if (!test_ttf.loadFromRenderedText("Test", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void renderTextures() 
{
	//test_image.render(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	//test_ttf.render(0,0);
	wall_img.render(0,0);
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
							case SDLK_q:
								quit = true;
								break;
						}
					}
				} 
				renderTextures();
				SDL_RenderPresent(p_game->getRenderer());
			}
		}
	}

	close();
	delete p_game;
	return 0;
}
