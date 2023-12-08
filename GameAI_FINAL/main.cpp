#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

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

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init() 
{
	bool success = true;

	//initialize sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else 
	{
		//Create window
		gWindow = SDL_CreateWindow("Game AI Final", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) 
		{
			printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) 
			{
				printf("SDL_image could not initialize! SDL_image Error %s\n", IMG_GetError());
				success = false;
			}
			else 
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

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

	//Quit SDL
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!init()) 
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
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	close();
	return 0;
}
