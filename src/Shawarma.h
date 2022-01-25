#pragma once
class Shawarma
{
private:
	//Shape
	sf::CircleShape shape;
	sf::RenderTarget& target;
public:
	//Constructors 
	Shawarma(sf::RenderTarget& target, sf::Texture* texture, sf::Vector2f map_size);

	//Accesors
	const sf::FloatRect getGlobal() const;
	unsigned int index;
	//Functions
	void render();
};

