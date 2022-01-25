#pragma once	
#include "Gui.h"
#include "CharactersMenu.h"
#include "State.h"
class PauseMenu
{
private:
	sf::RenderWindow& window;
	sf::VideoMode& resolution;

	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape container;
	sf::RectangleShape background;

	std::map<std::string, gui::Button*> buttons;
	float btnWidth;
	float btnHeight;
	std::map<std::string, float> btnX;
	std::map<std::string, float> btnY;

	std::unique_ptr<CharactersMenu> charactersMenu;

	//Saving a reference of the state to use the getKeytime function we need for input
	State& state;
private:
	void updateSizes();
	void updatePositions();

	void updateInput();
public:
	bool inPauseMenu;
	PauseMenu(sf::RenderWindow& window, sf::Font& font, sf::Texture* texture_sheet, State& state, Player& player, sf::VideoMode& resolution);
	virtual ~PauseMenu();

	//Functions
	const bool isButtonPressed(const std::string& key);
	void updateResolution(sf::RenderWindow& window);

	void update(sf::Vector2f& mousePos);
	void render();

};

