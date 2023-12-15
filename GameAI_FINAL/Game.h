#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Game
{
public:
	static Game* getInstance();
	static void createInstance();
	static void deleteInstance() { delete mp_instance; };
	Game() {};
	~Game();
	Game(const Game& obj) = delete; // cannot have a copy constructor
	bool init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

	SDL_Renderer* getRenderer() { return mp_Renderer; };
	SDL_Window* getWindow() { return mp_Window; };
	TTF_Font* getFont() { return mp_Font; };

	bool setFont(std::string filename, float size);
private:
	void close();
	int SCREEN_W = 0;
	int SCREEN_H = 0;
	static Game* mp_instance;

	SDL_Window* mp_Window = NULL;
	SDL_Renderer* mp_Renderer = NULL;
	TTF_Font* mp_Font = NULL;
};

