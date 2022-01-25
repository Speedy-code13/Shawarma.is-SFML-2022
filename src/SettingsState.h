#pragma once
#include "State.h"
class SettingsState :
    public State
{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*>  buttons;
	std::map<std::string, gui::DropDownList*>  dropDownLists;

	sf::Text optionsText;	

	std::vector<sf::VideoMode> modes;
	std::vector<unsigned> fps;

	std::map<std::string, unsigned> activeElements;

	//Private Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initGui();
	void initText();

	void updatePositions();
public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //Functions
	void endState();

	void loadSettings();
	void saveSettings();

	void updateResolution();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update();
	void renderGui(sf::RenderTarget& target);
	void render();

};

