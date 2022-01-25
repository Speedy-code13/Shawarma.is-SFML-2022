#include "pch.h"
#include "GameState.h"

void GameState::initVariables()
{
	this->spawnTimerMax = 0.010f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxShawarmas = 200;
	this->massDivider = 3;
	this->initialSize = 350;
	this->mass = this->initialSize;
	this->shawarmasInView.reserve(maxShawarmas / 10);
}

void GameState::initTextures()
{	
	this->textures["SHAWARMA"].loadFromFile("Resources/Images/Players/shaorma.png");	
	this->textures["PLAYER"].loadFromFile("Resources/Images/Players/player_sheet.png");
}

void GameState::initFont()
{
	this->font.loadFromFile("Resources/Fonts/Dosis-Light.ttf");
}

void GameState::initPauseMenu()
{
	this->pauseMenu = std::make_unique<PauseMenu>(*this->window, this->font, &this->textures["PLAYER"], *this, *this->player, this->resolution);
}

void GameState::initMap()
{
	this->gridSize = 512.f;
	this->mapSize = { 5120.f, 2560.f };
	this->mapRect.setFillColor(sf::Color::Transparent);
	this->mapRect.setOutlineColor(sf::Color::Red);
	this->mapRect.setOutlineThickness(10.f);
	this->mapRect.setSize(this->mapSize);
//	this->mapRect.setTexture(&this->textures["BG"]);
	this->map = std::make_unique<TileMap>(this->gridSize, static_cast<unsigned>(this->mapSize.x / this->gridSize) , static_cast<unsigned>(this->mapSize.y / this->gridSize ));
}

void GameState::initPlayer()
{
	this->player = std::make_unique<Player>(*this->window, this->mapSize , static_cast<float>(this->initialSize / massDivider));
	this->player->setTexture(&this->textures["PLAYER"]);
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(static_cast<float>(this->window->getPosition().x),
		static_cast<float>(this->window->getPosition().y) 
		)
	);
	this->view.setCenter(sf::Vector2f(static_cast<float>(this->window->getPosition().x) / 2.f,
		static_cast<float>(this->window->getPosition().y / 2.f)));
}

void GameState::endState()
{
	this->saveSettings();
	this->quit = true;
}

void GameState::printPosition(float delay)
{
	if (posClock.getElapsedTime().asSeconds() >= delay)
	{
		std::cout << "Pos X:"
			<< player->getPosition().x
			<< "\n"
			<< "Pos Y:"
			<< player->getPosition().y
			<< "\n";
		posClock.restart();
	}
}

void GameState::updateView()
{
	this->view.setCenter(
		this->player->getPosition().x + this->player->getSize().x / 2.f,
		this->player->getPosition().y + this->player->getSize().y / 2.f
	);

	this->view.setSize(
		static_cast<float>(this->window->getSize().x + mass / this->massDivider), 
		static_cast<float>(this->window->getSize().y + mass / this->massDivider)
	);
	//this->view.setSize(this->mapSize);
}

void GameState::playerDeath()
{
	this->mass = initialSize;
	this->player->updateSize(static_cast<float>(mass / massDivider));
	this->player->setPosition(static_cast<float>(rand() % int(this->mapSize.x)), static_cast<float>(rand() % int(this->mapSize.y)));

	this->endState();
}

void GameState::updateResolution()
{
	this->pauseMenu->updateResolution(*this->window);
	this->updatedRes = true;
}

void GameState::updateMassText()
{
	std::stringstream ss;
	ss << "Mass: " << this->mass;
	this->massText.setString(ss.str());
}

void GameState::updatePlayer()
{	
	this->player->update(*this->dt);

	//Move Left
	if (this->player->getGlobal().left <= 0.f)
		this->playerDeath();
	//Move Right
	else if (this->player->getGlobal().left + this->player->getGlobal().width >= this->mapSize.x) 
		this->playerDeath();
	//Move Up
	if (this->player->getGlobal().top <= 0.f) 
		this->playerDeath();
	//Move Down
	else if (this->player->getGlobal().height + this->player->getGlobal().top >= this->mapSize.y) 
		this->playerDeath();
}

void GameState::renderShawarmas()
{
	for (auto it : this->shawarmasInView)
		it->render();
}

void GameState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeytime())
	{
		this->pauseMenu->inPauseMenu = true;
	}
}

void GameState::updateShawarmas()
{
	shawarmasInView.clear();

	for (int i = 0; i < shawarmas.size(); i++) //Adds shawarmas to the array if they are in view
	{
		if (isRectInView(shawarmas[i]->getGlobal())) 
		{
			shawarmas[i]->index = i;
			shawarmasInView.push_back(shawarmas[i]);
		}
	}

	for (auto shawarma : shawarmasInView)
	{
		//Checks if player collides with shawarmas in view
		if (this->player->getGlobal().intersects(this->shawarmas[shawarma->index]->getGlobal()))
		{
			this->mass++;
			this->player->updateSize(static_cast<float>(this->mass / massDivider));

			//Deletes the shawarma from the mother array
			this->shawarmas.erase(this->shawarmas.begin() + shawarma->index);
		}
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
}

const bool GameState::isRectInView(sf::FloatRect rect) const
{
	sf::Vector2f viewCenter(view.getCenter());
	sf::Vector2f viewSize(view.getSize());

	sf::FloatRect viewRect(viewCenter - viewSize / 2.f, viewSize);

	return viewRect.intersects(rect);
}

void GameState::spawnShawarmas()
{
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += *this->dt;
	}
	else if (this->shawarmas.size() < this->maxShawarmas)
	{
		this->shawarmas.push_back(new Shawarma(*this->window, &this->textures["SHAWARMA"], this->mapSize));
		spawnTimer = 0.f;
	}
}	

void GameState::saveSettings()
{
	std::ofstream ofs("Resources/Saves/game.txt");
	{
		if (ofs.is_open())
		ofs << this->mass << "\n";
		ofs << this->player->getPosition().x << "\n";
		ofs << this->player->getPosition().y << "\n";
		ofs.close();
	}
}

void GameState::loadSettings()
{
	std::ifstream ifs("Resources/Saves/game.txt");
	if (ifs.is_open())
	{
		float x, y;
		ifs >> this->mass;
		ifs >> x;
		ifs >> y;
		ifs.close();
		this->player->setPosition(x, y);
		this->player->updateSize(static_cast<float>(this->mass / massDivider));
	}
}

GameState::GameState(StateData* stateData, bool new_game, sf::Music* music)
	: State(stateData), music(music)
{
	this->initVariables();
	this->initTextures();
	this->initFont();
	this->initMap();
	this->initPlayer();
	this->initView();
	this->initPauseMenu();
	this->massText.setFont(this->font);
	if (!new_game) this->loadSettings();
}

GameState::~GameState()
{
	for (auto* it : this->shawarmas)
		delete it;
}

void GameState::update()
{
	this->updateMousePositions();
	this->updateKeytime();

	if (!this->pauseMenu->inPauseMenu) // Unpaused state
	{
		this->updateInput();
		
		this->map->update(static_cast<sf::Vector2i>(this->player->getPosition() / 512.f), static_cast<sf::Vector2i>(this->view.getSize() / 512.f));
		this->updatePlayer();
		this->updateView();
		this->updateMassText();
		this->updateShawarmas();
		this->spawnShawarmas();
	}
	else // Paused State
	{
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void GameState::render()
{
	this->window->setView(this->view); // Render Game Stuff	

	this->map->render(*this->window);
	this->window->draw(this->mapRect);

	this->renderShawarmas();

	this->player->render();

	this->window->setView(this->window->getDefaultView()); // Render UI	
	this->window->draw(this->massText);

	if (this->pauseMenu->inPauseMenu)
		this->pauseMenu->render();
}
