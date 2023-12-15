#include "Tile.h"

Tile::Tile() 
{
	x = 0;
	y = 0;
}

Tile::Tile(Texture _texture) 
{
	x = 0;
	y = 0;
	m_texture = _texture;
}

Tile::~Tile() 
{
}

void Tile::setPosition(float _x, float _y) 
{
	x = _x;
	y = _y;
}

void Tile::render() 
{
	m_texture.render(x, y);
}