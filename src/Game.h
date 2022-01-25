#pragma once
#include "MainMenuState.h"
#include "GraphicsSettings.h"
class Game
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;	
	GraphicsSettings gfx;

	std::stack<State*> states;
	bool updatedRes;

	StateData stateData;

	sf::Clock dtClock;
	float dt;
private:
	//Initializers
	void initVariables();
	void initWindow();
	void initStates();
	
	//Private Functions
	void updateResolution();
	void updateEvents();
	void updateDt();

	void endApplication();

	void update();
	void render();
public:
	//Constructor & Deconstructor
	Game();
	~Game();

	//Game core
	void run();
};

