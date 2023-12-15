#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Game.h"
class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(std::string path);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	void free();

	void render(int x, int y);

	int getWidth() { return m_Width; };
	int getHeight() { return m_Height; };

private:
	SDL_Texture* mp_Texture;

	int m_Width;
	int m_Height;
};

