#pragma once
class Player
{
private:
	sf::Vector2f mapSize;
	float movementSpeed;
	sf::RenderWindow& window;
	sf::RectangleShape obj;
public:
	//Constructor
	Player(sf::RenderWindow& window, const sf::Vector2f map_size, const float initialSize);
	
	//Initializer Functions
	void initObj(const float initialSize);

	//Accesors
	void setTexture(sf::Texture* texture);
	void setTextureRect(sf::IntRect rect);
	void setPosition(float x, float  y);
	void setMovementSpeed(float movement_speed);

	void loadTextureRect();

	const sf::FloatRect getGlobal() const;
	const sf::Vector2f getSize() const;
	const sf::Vector2f getPosition() const;

	//Functions
	void updateSize(float mass);

	void update(const float& dt);
	void render();
};

