#pragma once
#include "GameState.h"
#include "SettingsState.h"
class MainMenuState : public State
{
private:
	enum class MusicBtnState{ MAX = 0, LOWER, OFF };
	MusicBtnState buttonState;

	sf::Font font;

	sf::RectangleShape background;

	std::vector<sf::Music*> musics;
	sf::RectangleShape musicButton;
	sf::Music* music;
	sf::IntRect currentMusicRect;

	unsigned short numberOfMusics;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
private:
	//Initializers
	void initVariables();
	void initFont();
	void initTextures();
	void initMusicButton();
	void initBackground();
	void initButtons();

	//Private Functions
	void positionButton(const std::string &name, const float offset);
	void positionAllButtons();
	void updateInput();
	void updateMusicButton();
	void updateResolution();
	void updateButtons();

	void saveSettings();
	void loadSettings();
	void loadMusics();

	void endState();
public:
	//Constructor & Deconstructor
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	void update();
	void render();
};

