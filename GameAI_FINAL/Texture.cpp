#include "Texture.h"

Texture::Texture() 
{
	mp_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
}

Texture::~Texture() 
{
	//deallocates memory
	free();
}

bool Texture::loadFromFile(std::string path) 
{
	//get rid of pre-existing texture
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) 
	{
		printf("Unable to load image %s! SDL_image Error",path.c_str(), IMG_GetError());
	}
	else 
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		//create texture from surface pixels
		SDL_Renderer* p_Renderer = Game::getInstance()->getRenderer();
		newTexture = SDL_CreateTextureFromSurface(p_Renderer, loadedSurface);
		if (newTexture == NULL) 
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else 
		{
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	mp_Texture = newTexture;
	return mp_Texture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor) 
{
	//get rid of pre-existing texture
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(Game::getInstance()->getFont(),textureText.c_str(), textColor);
	if (textSurface == NULL) 
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

	}
	else 
	{
		//create texture from surface pixels
		mp_Texture = SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(), textSurface);
		if (mp_Texture == NULL) 
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else 
		{
			m_Width = textSurface->w;
			m_Height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mp_Texture != NULL;
}

void Texture::free()
{
	if (mp_Texture != NULL) 
	{
		SDL_DestroyTexture(mp_Texture);
		mp_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void Texture::render(int x, int y) 
{
	//set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };
	SDL_RenderCopy(Game::getInstance()->getRenderer(), mp_Texture, NULL, &renderQuad);
}