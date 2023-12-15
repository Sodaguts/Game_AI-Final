#pragma once
#include "Texture.h"
class Tile
{
public:
	Tile();
	Tile(Texture _texture);
	~Tile();

	void setTexture(Texture _texture) { mp_texture = &_texture; };
	Texture* getTexture() { return mp_texture; };
	void setPosition(float x, float y);
	void render();

	float getX() { return x; };
	float getY() { return y; };

private:
	float x, y;
	Texture* mp_texture;
};

