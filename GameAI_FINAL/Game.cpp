#include "Game.h"

Game* Game::mp_instance = nullptr;

Game* Game::getInstance() 
{
	return mp_instance;
}

void Game::createInstance() 
{
	mp_instance = new Game();
}

Game::~Game() 
{
	close();
}

bool Game::init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT) 
{
	bool success = true;
	SCREEN_W = SCREEN_WIDTH;
	SCREEN_H = SCREEN_HEIGHT;

	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else 
	{
		//init window
		mp_Window = SDL_CreateWindow("Game AI Final", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mp_Window == NULL) 
		{
			printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}
		else 
		{
			//init renderer
			mp_Renderer = SDL_CreateRenderer(mp_Window, -1, SDL_RENDERER_ACCELERATED);
			if (mp_Renderer == NULL) 
			{
				printf("Renderer could not be created! SDL_ERROR: %s\n", SDL_GetError());
				success = false;
			}
			else 
			{
				SDL_SetRenderDrawColor(mp_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

void Game::close() 
{
	SDL_DestroyRenderer(mp_Renderer);
	SDL_DestroyWindow(mp_Window);
	mp_Renderer = NULL;
	mp_Window = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}