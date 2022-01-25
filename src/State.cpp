#include "pch.h"
#include "State.h"		


State::State(StateData* stateData)
	: resolution(stateData->gfx->resolution), stateData(stateData)
{
	this->window = this->stateData->window;
	this->dt = this->stateData->dt;
	this->states = this->stateData->states;
	
	this->quit = false;
	this->updatedRes = false;

	this->keytimeMax = 10.f;
	this->keytime = keytimeMax;
}

void State::updateKeytime()
{
	if (this->keytime <= keytimeMax)
		this->keytime += 50.f * (*dt);
}

const bool State::getQuit() const 
{ 
	return this->quit;
}

const bool State::getUpdatedRes() const 
{ 
	return this->updatedRes; 
}

void State::endState()
{	
	this->quit = true;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}






