#include "pch.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setPosition({ x, y });
	this->shape.setTexture(&texture);
}


Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
