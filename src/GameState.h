#pragma once
#include "Player.h"
#include "Shawarma.h"
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
class GameState : public State
{
private:

	//Variables
	sf::Font font;

	std::unique_ptr<TileMap> map;
	sf::Vector2f mapSize;
	sf::RectangleShape mapRect;

	std::unique_ptr<Player> player;
	sf::View view;

	std::vector<Shawarma*> shawarmas;
	std::vector<Shawarma*> shawarmasInView;
	sf::Text massText;
	unsigned int maxShawarmas;

	unsigned int mass;
	unsigned int initialSize;

	float spawnTimer;
	float spawnTimerMax;

	sf::Music* music;

	int massDivider;

	std::unique_ptr<PauseMenu> pauseMenu;
	float gridSize;

	sf::Clock posClock;

		
	//Initializers
	void initVariables();
	void initTextures();
	void initFont();
	void initPauseMenu();
	void initMap();
	void initPlayer();
	void initView();

	//Functions
	void spawnShawarmas();
	void saveSettings();
	void loadSettings();
	void endState();
	void playerDeath();

	void printPosition(float delay);
	void updateView();
	void updateResolution();
	void updateMassText();
	void updatePlayer();
	void updateInput();
	void updateShawarmas();
	void renderShawarmas();

	void updatePauseMenuButtons();

	const bool isRectInView(sf::FloatRect rect) const;

public:
	//Constructor & Deconstructor
	GameState(StateData* stateData, bool new_game, sf::Music* music);
	virtual ~GameState();

	void update();
	void render();
};