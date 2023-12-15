#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "Game.h"
#include "Texture.h"
#include "Tile.h"
#include <vector>
#include <iostream>
#include <queue>

//Screen dimension constants
const int SCREEN_WIDTH = 609;
const int SCREEN_HEIGHT = 480;

const std::string IMAGE_FILENAME = "Images/Image_47.bmp";
const std::string T_WALL_FILENAME = "Images/wall.png";
const std::string T_PATH_FILENAME = "Images/floor.png";
const std::string TEST_IMG_FILENAME = "Images/cheeks.png";
const std::string T_ALT_FILENAME = "Images/blackbox.png";
const std::string TEST_FONT_FILENAME = "Fonts/Alice-Regular.ttf";

const int MAP_BOUNDARY_TOP_LEFT_X = 32;
const int MAP_BOUNDARY_TOP_LEFT_Y = 32;
const int MAP_BOUNDARY_BOT_RIGHT_X = (SCREEN_WIDTH / 32) - 2;
const int MAP_BOUNDARY_BOT_RIGHT_Y = (SCREEN_HEIGHT / 32) - 2;

bool loadMedia();
void close();
void renderTextures();

void createTiles();

SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gImage = NULL;

Texture test_image;
Texture test_ttf;
Texture wall_img;
Texture floor_img;

Tile m_tile;
std::vector<Tile> tiles;

bool showHelp = true;
bool generateMap = true;

void GenerateMap();
std::vector<std::pair<int, int>> positions;

void clear();

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

	if (!floor_img.loadFromFile(T_ALT_FILENAME)) 
	{
		printf("Failed to load floor image!\n");
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
		if (!test_ttf.loadFromRenderedText("Q to Quit, H for Help, R to regenerate map", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}


void GenerateMap() 
{
	enum directions 
	{
		NORTH,
		SOUTH,
		EAST,
		WEST
	};

	int MAX_BOUND_X = MAP_BOUNDARY_BOT_RIGHT_X;
	int MIN_BOUND_X = MAP_BOUNDARY_TOP_LEFT_X;
	int MAX_BOUND_Y = MAP_BOUNDARY_BOT_RIGHT_Y;
	int MIN_BOUND_Y = MAP_BOUNDARY_TOP_LEFT_Y;
	int step = 32;
	int numRooms = 5;
	int startPosX = 3 * step;
	int startPosY = 2 * step;
	int currentPosX = startPosX;
	int currentPosY = startPosY;
	std::queue<std::pair<int, int>> queue;
	//Choose random direction (go to neighbor by adding +32/-32/+32/-32)
	for (int i = 0; i < numRooms; i++) 
	{
		int randNum = 0 + (rand() % 3);
		switch (randNum) 
		{
			case NORTH:
				currentPosY += step;
				break;
			case SOUTH:
				currentPosY -= step;
				break;
			case EAST:
				currentPosX += step;
				break;
			case WEST:
				currentPosX -= step;
				break;
			default:
				break;
		}
		//- if neighbor is greater than MAX_BOUND or less than MIN_BOUND, end
		if ((currentPosX >= MAX_BOUND_X) || (currentPosX <= MIN_BOUND_X) || (currentPosY >= MAX_BOUND_Y) || (currentPosY <= MIN_BOUND_Y)) 
		{
			break;
		}
		else 
		{
			//- if neighbor has more than one filled neighbor, end
			//- if MAX_ROOMS has been reached, end
			//- Random 50% chance, end
			//Otherwise mark neighbor cell as room(floor.png), add to queue
		}
		
	}
	generateMap = false;
}

void createTiles() 
{
	
	for (int i = 0; i < SCREEN_WIDTH; i++) 
	{
		m_tile.setTexture(wall_img);
		m_tile.setPosition(m_tile.getX() + 32, m_tile.getY());
		tiles.push_back(m_tile);
	}
	std::cout << tiles.size() << std::endl;
}

void renderTextures() 
{
	//test_image.render(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
	//test_ttf.render(0,0);
	//Create outer walls
	int currentX = 0;
	int currentY = 0;
	for (int i = 0; i < SCREEN_HEIGHT/32; i++) 
	{
		for (int j = 0; j < SCREEN_WIDTH/32; j++) 
		{
			wall_img.render(currentX, currentY);
			currentX += 32;
		}
		currentX = 0;
		currentY += 32;
	}
	//wall_img.render(0,0);
	//floor_img.render(32,32);
	//Test function : render random walkable tiles
	int floorCurrentX = 32;
	int floorCurrentY = 32;
	
	if (generateMap == true) 
	{
		positions.clear();
		printf("first");
		for (int i = 0; i < MAP_BOUNDARY_BOT_RIGHT_Y; i++)
		{
			for (int j = 0; j < MAP_BOUNDARY_BOT_RIGHT_X; j++)
			{
				int randNum = 0 + (rand() % 2);
				if (randNum == 0)
				{
					//floor_img.render(floorCurrentX, floorCurrentY);
					std::pair<int, int> pos = {floorCurrentX,floorCurrentY};
					positions.push_back(pos);
				}
				floorCurrentX += 32;
			}
			floorCurrentX = 32;
			floorCurrentY += 32;
		}
		generateMap = false;
	}
	//generateMap = false;
	for (int i = 0; i < positions.size(); i++) 
	{
		std::cout << positions[i].first <<"," <<positions[i].second << std::endl;

		floor_img.render(positions[i].first, positions[i].second);
	}

	if (showHelp == true) 
	{
		test_ttf.render(0,0);
	}
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
							case SDLK_h:
								showHelp = !showHelp;
								break;
							case SDLK_r:
								generateMap = true;
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
