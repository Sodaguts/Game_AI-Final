#pragma once
#include "Texture.h"
class Tile
{
public:
	Tile();
	~Tile();

	void setTexture(Texture* p_texture);
	Texture* getTexture() { return mp_texture; };
private:
	float x, y;
	Texture* mp_texture;
};

