#include "pch.h"
#include "PauseMenu.h"


const bool PauseMenu::isButtonPressed(const std::string& key) 
{
	return this->buttons[key]->isPressed(); 
}

void PauseMenu::updateResolution(sf::RenderWindow& window)
{
	this->updateSizes();
	this->updatePositions();

	this->buttons["QUIT"]->setPosition(this->btnX["QUIT"], this->btnY["QUIT"]);
	this->buttons["CHARACTERS"]->setPosition(this->btnX["CHARACTERS"], this->btnY["CHARACTERS"]);
	
	this->charactersMenu->updateResolution();
}

void PauseMenu::updateSizes()
{
	//Init background
	this->background.setSize(
		{
		static_cast<float>(this->resolution.width),
		static_cast<float>(this->resolution.height)
		}
	);

	//Init container
	this->container.setSize(
		{
		static_cast<float>(this->resolution.width) / 4.f,
		static_cast<float>(this->resolution.height - 100.f)
		}
	);

}

void PauseMenu::updatePositions()
{
	this->container.setPosition(
		static_cast<float>(this->resolution.width) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);

	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);
	this->btnX["QUIT"] = this->container.getPosition().x + this->container.getSize().x / 2.f - this->btnWidth / 2.f;
	this->btnY["QUIT"] = this->container.getSize().y - 100.f;

	this->btnX["CHARACTERS"] = this->btnX["QUIT"];
	this->btnY["CHARACTERS"] = this->container.getSize().y / 2.f - this->btnHeight / 2.f;
}

void PauseMenu::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->state.getKeytime())
	{
		if (this->charactersMenu->inChMenu) 
		{
			this->charactersMenu->inChMenu = false;
		}
		else
		{
			this->inPauseMenu = false;
		}
	}
}

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font, sf::Texture* texture_sheet, State& state, Player& player, sf::VideoMode& resolution)
	: font(font), window(window), inPauseMenu(false), state(state), resolution(resolution)
{
	//Init background
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container

	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("Paused");

	this->btnWidth = 250.f;
	this->btnHeight = 50.f;


	this->updateSizes();
	this->updatePositions();
	
	//Initializing the quit button
	this->buttons["QUIT"] = new gui::Button(
		0.f, 0.f, this->btnWidth, this->btnHeight,
		&this->font, "Quit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["QUIT"]->setPosition(this->btnX["QUIT"], this->btnY["QUIT"]);

	//Initializing the characters button
	this->buttons["CHARACTERS"] = new gui::Button(
		0.f, 0.f, this->btnWidth, this->btnHeight,
		&this->font, "Characters", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["CHARACTERS"]->setPosition(this->btnX["CHARACTERS"], this->btnY["CHARACTERS"]);

	this->charactersMenu = std::make_unique<CharactersMenu>(this->window, font, texture_sheet, player, resolution);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void PauseMenu::update(sf::Vector2f& mousePos)
{
	this->updateInput();
	if (!this->charactersMenu->inChMenu) //Update pause menu
	{
		for (auto& i : this->buttons)
		{
			i.second->update(mousePos);
		}
		if (this->buttons["CHARACTERS"]->isPressed())
		{
			this->charactersMenu->inChMenu = true;
		}
	}
	else // Update characters menu
	{
		this->charactersMenu->update(mousePos);
	}

}

void PauseMenu::render()
{
	if (!this->charactersMenu->inChMenu) // Render Pause Menu
	{
		this->window.draw(this->background);
		this->window.draw(this->container);
		this->window.draw(this->menuText);
		for (auto& i : this->buttons)
		{
			i.second->render(window);
		}
	}
	else //Render characters menu
	{
		this->charactersMenu->render();
	}

}
