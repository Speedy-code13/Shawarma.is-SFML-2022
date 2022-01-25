#include "pch.h"
#include "Shawarma.h"

Shawarma::Shawarma(sf::RenderTarget& target, sf::Texture* texture, sf::Vector2f map_size)
	: target(target)
{
	this->index = -1;
	this->shape.setRadius(static_cast<float>(rand() % 30 + 15));
	this->shape.setPosition(
		sf::Vector2f(
			static_cast<float>(rand() % int(map_size.x - this->shape.getGlobalBounds().width)),
			static_cast<float>(rand() % int(map_size.y - this->shape.getGlobalBounds().height))
		)
	);
	this->shape.setTexture(texture);
}

const sf::FloatRect Shawarma::getGlobal() const
{
	return this->shape.getGlobalBounds();
}

void Shawarma::render()
{
	this->target.draw(this->shape);
}
