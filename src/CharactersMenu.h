#pragma once
#include "Gui.h"
#include "Player.h"
class CharactersMenu
{
private:
	sf::RenderWindow& window;
	sf::VideoMode& resolution;

	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Text menuText;

	std::unique_ptr<gui::Button> backBtn;
	float btnX, btnY;
	float widthBtn, heightBtn;
	std::unique_ptr<gui::TextureSelector> charactersSelector;

	float textSX, textSY;
	float widthTextS, heightTextS;

	Player& player;
private:
	void updateSizes();
	void updatePositions();

public:
	bool inChMenu;

public:
	CharactersMenu(sf::RenderWindow& window, sf::Font& font, sf::Texture* texture_sheet, Player& player, sf::VideoMode& resolution);
	
	void updateResolution();
	void saveTextureRect(sf::IntRect rect);

	void update(sf::Vector2f mousePos);
	void render();

};