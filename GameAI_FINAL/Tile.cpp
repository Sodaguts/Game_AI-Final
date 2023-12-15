#include "Tile.h"

Tile::Tile() 
{
	x = 0;
	y = 0;
	mp_texture = NULL;
}

Tile::Tile(Texture _texture) 
{
	x = 0;
	y = 0;
	mp_texture = &_texture;
}

Tile::~Tile() 
{
	delete mp_texture;
	mp_texture = NULL;
}

void Tile::setPosition(float _x, float _y) 
{
	x = _x;
	y = _y;
}

void Tile::render() 
{
	mp_texture->render(x, y);
}