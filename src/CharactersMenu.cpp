#include "pch.h"
#include "CharactersMenu.h"

void CharactersMenu::updateSizes()
{
	//Init background
	this->background.setSize({
		static_cast<float>(this->resolution.width),
		static_cast<float>(this->resolution.height)
		});

	//Init container
	this->container.setSize({
		static_cast<float>(this->resolution.width) / 2.f,
		static_cast<float>(this->resolution.height - 100.f)
		});

}

void CharactersMenu::updatePositions()
{
	this->container.setPosition(
		static_cast<float>(this->resolution.width) / 2.f - this->container.getSize().x / 2.f,
		30.f
	);
		
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);
	this->btnX = this->container.getPosition().x + this->container.getSize().x - this->widthBtn + 70.f;
	this->btnY = this->container.getPosition().y + this->container.getSize().y - this->heightBtn - 20.f;

	this->backBtn->setPosition(this->btnX, this->btnY);

	this->textSX = this->container.getPosition().x + this->container.getSize().x / 2.f - this->widthBtn;
	this->textSY = this->container.getPosition().y  + 150.f - this->heightBtn;
	this->charactersSelector->setPosition(this->textSX, this->textSY);
}

void CharactersMenu::updateResolution()
{
	this->updateSizes();
	this->updatePositions();
}

void CharactersMenu::saveTextureRect(sf::IntRect rect)
{
	std::ofstream ofs("Resources/Saves/player.txt");
	if (ofs.is_open())
	{
		ofs << rect.top << "\n" << rect.left;
		ofs.close();
	}
}

CharactersMenu::CharactersMenu(sf::RenderWindow& window, sf::Font& font, sf::Texture* texture_sheet, Player& player, sf::VideoMode& resolution)
	:window(window), inChMenu(false), player(player), resolution(resolution)
{
	//Init background
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("Select your Character");

	this->widthBtn = 250.f;
	this->heightBtn = 50.f;
	this->backBtn = std::make_unique<gui::Button>(0.f, 0.f, this->widthBtn, this->heightBtn,
		&font, "Back", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	this->widthTextS = 500.f;
	this->heightTextS = 500.f;

	this->charactersSelector = std::make_unique<gui::TextureSelector>(0.f, 0.f, this->widthTextS, this->heightTextS, 250.f, texture_sheet);

	this->updateSizes();
	this->updatePositions();
}

void CharactersMenu::update(sf::Vector2f mousePos)
{
	this->backBtn->update(mousePos);

	if (this->backBtn->isPressed())
		this->inChMenu = false;

	this->charactersSelector->update(static_cast<sf::Vector2i>(mousePos));

	//If the left button is press we select the character and set it to the player
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->player.setTextureRect(this->charactersSelector->getTextureRect());
		this->saveTextureRect(this->charactersSelector->getTextureRect());
	}
}

void CharactersMenu::render()
{
	this->window.draw(this->background);
	this->window.draw(this->container);
	this->window.draw(this->menuText);
	this->backBtn->render(this->window);
	this->charactersSelector->render(this->window);
}
