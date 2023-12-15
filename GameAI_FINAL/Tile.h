#pragma once
#include "Texture.h"
class Tile
{
public:
	Tile();
	Tile(Texture _texture);
	~Tile();

	void setTexture(Texture _texture) { m_texture = _texture; };
	Texture getTexture() { return m_texture; };
	void setPosition(float x, float y);
	void render();

	float getX() { return x; };
	float getY() { return y; };

private:
	float x, y;
	Texture m_texture;
};

