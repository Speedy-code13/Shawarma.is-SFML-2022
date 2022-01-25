#include "pch.h"
#include "Player.h"

void Player::initObj(const float initialSize)
{	
	this->obj.setSize(sf::Vector2f( initialSize, initialSize));

	float adjustedInitialSize = initialSize * 2.f;

	float posX = static_cast<float>(rand() % int(this->mapSize.x - adjustedInitialSize) + adjustedInitialSize);
	float posY = static_cast<float>(rand() % int(this->mapSize.y - adjustedInitialSize) + adjustedInitialSize);

	this->obj.setPosition(posX, posY);
}

void Player::setTexture(sf::Texture* texture) { this->obj.setTexture(texture); }

void Player::setTextureRect(sf::IntRect rect)
{
	this->obj.setTextureRect(rect);
}

void Player::setPosition(float x, float y) { this->obj.setPosition({ x, y }); }

void Player::setMovementSpeed(float movement_speed) { this->movementSpeed = movement_speed; }

void Player::loadTextureRect()
{
	int top = 0;
	int left = 0;
	std::ifstream ifs("Resources/Saves/player.txt");
	if (ifs.is_open())
	{
		ifs >> top;
		ifs >> left;
		ifs.close();
	}
	this->obj.setTextureRect(sf::IntRect(left, top, 250, 250));
}

const sf::FloatRect Player::getGlobal() const {	return this->obj.getGlobalBounds(); }

const sf::Vector2f Player::getSize() const { return this->obj.getSize(); }

const sf::Vector2f Player::getPosition() const { return this->obj.getPosition(); }

void Player::updateSize(float mass)
{
	this->obj.setSize({ mass, mass });
}

Player::Player(sf::RenderWindow& window, const sf::Vector2f map_size, const float initialSize)
	: mapSize(map_size), window(window), movementSpeed(300.f)
{
	this->initObj(initialSize);
	this->loadTextureRect();
}

void Player::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		obj.move(0.f, (this->movementSpeed * -1.f) * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		obj.move(0.f, (this->movementSpeed * 1.f) * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		obj.move((this->movementSpeed * 1.f) * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		obj.move((this->movementSpeed * -1.f) * dt, 0.f);
	}
}

void Player::render()
{
	this->window.draw(this->obj);
}
