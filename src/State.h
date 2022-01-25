#pragma once
#include "Gui.h"
#include "GraphicsSettings.h"
class State;
struct StateData
{
	std::shared_ptr<sf::RenderWindow> window;
	const float* dt;
	std::stack<State*>* states;
	GraphicsSettings* gfx;
	StateData()
	{
		this->window = nullptr;
		this->dt = nullptr;
		this->states = nullptr;
		this->gfx = nullptr;
	}
};
class State
{
private:
	float keytime;
	float keytimeMax;

protected:
	StateData* stateData;
	std::shared_ptr<sf::RenderWindow> window;
	std::stack<State*>* states;
	std::map<std::string, sf::Texture> textures;

	sf::VideoMode& resolution;

	bool updatedRes;

	const float* dt;
	
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

protected:
	void updateKeytime();
	virtual void updateMousePositions();

public:
	//Constructor
	State(StateData* stateData);

	//Accesors
	const bool getQuit() const;
	const bool getUpdatedRes() const;
	//Functions	
	const bool getKeytime();
	virtual void endState();

	virtual void updateResolution() = 0;
	virtual void saveSettings() = 0;

	virtual void render() = 0;
	virtual void update() = 0;

};

