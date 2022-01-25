#include "pch.h"
#include "MainMenuState.h"

void MainMenuState::updateResolution()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfx->resolution.width), static_cast<float>(this->stateData->gfx->resolution.height)));
	this->positionAllButtons();
	this->musicButton.setPosition({ 0.f, this->resolution.height - this->musicButton.getGlobalBounds().height });
}

void MainMenuState::updateButtons()
{
	for (auto& i : buttons)
		i.second->update(this->mousePosView);

	if (this->buttons["NEW_GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData, true, this->music));
	}

	else if (this->buttons["LOAD_GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData,false, this->music));
	}

	else if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}
	else if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->stateData->gfx->saveToFile("Config/graphics.ini");
		this->saveSettings();
		this->window->close();
	}
}

void MainMenuState::saveSettings()
{
	//Saving the state of the music button
	std::ofstream ofs("Config/main_menu_state.ini");
	if (ofs.is_open())
	{
		ofs << "#The state of the music button (MAX, LOWER, OFF):\n";
		ofs << static_cast<int>(this->buttonState);
		ofs.close();
	}
}

void MainMenuState::loadSettings()
{
	std::string comment;
	int music_button_value;
	std::ifstream ifs("Config/main_menu_state.ini");
	if (ifs.is_open()) //If the file is opened, read settings
	{
		std::getline(ifs, comment);
		ifs >> music_button_value;
		ifs.close();

		//Checks if the music_button_value is correct
		if(music_button_value >= 0 && music_button_value <= 2)
			this->buttonState = static_cast<MusicBtnState>(music_button_value);
	}
}

void MainMenuState::loadMusics()
{
	for (unsigned short i = 0; i < numberOfMusics; i++)
	{
		sf::Music* music = new sf::Music();
		
		if (music->openFromFile("Resources/Audio/melody" + std::to_string(i) + ".wav"))
			musics.push_back(music);
		else
			delete music;
	}
}

void MainMenuState::endState()
{
	this->quit = true;
}

void MainMenuState::positionButton(const std::string &name, const float offset)
{ 
	this->buttons[name]->setPosition(
		this->resolution.width / 2.f - this->buttons[name]->getGlobalBounds().width / 2.f,
		this->resolution.height / 2.f - this->buttons[name]->getGlobalBounds().height / 2.f + offset
	);
}

void MainMenuState::positionAllButtons()
{
	this->positionButton("NEW_GAME_STATE", -200.f);
	this->positionButton("LOAD_GAME_STATE", -100.f);
	this->positionButton("SETTINGS_STATE", 0.f);
	this->positionButton("EXIT_STATE", 100.f);
}

void MainMenuState::updateInput()
{
}

void MainMenuState::updateMusicButton()
{
	if (musics.empty()) return;
	if (this->musicButton.getGlobalBounds().contains(this->mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime() )
	{
		switch (this->buttonState)
		{
		case MusicBtnState::MAX:
			this->currentMusicRect.left = 100;
			this->music->setVolume(50.f);
			this->buttonState = MusicBtnState::LOWER;
			break;
		case MusicBtnState::LOWER:
			this->currentMusicRect.left = 200;
			this->music->stop();
			this->buttonState = MusicBtnState::OFF;
			break;
		case MusicBtnState::OFF:
			this->currentMusicRect.left = 0;
			this->music->stop();
			this->music = musics[rand() % musics.size()];
			this->music->setVolume(100.f);
			this->music->play();
			this->buttonState = MusicBtnState::MAX;

			break;
		}
		this->musicButton.setTextureRect(this->currentMusicRect);
	}
}

void MainMenuState::initVariables()
{
	this->buttonState = MusicBtnState::LOWER;
	this->numberOfMusics = 4;
	this->music = nullptr;
}

void MainMenuState::initFont()
{
	this->font.loadFromFile("Resources/Fonts/arial.ttf");
}

void MainMenuState::initTextures()
{
	this->textures["BACKGROUND"].loadFromFile("Resources/Images/Backgrounds/bg1.jpg");
	this->textures["MUSIC_BUTTON"].loadFromFile("Resources/Images/Buttons/music_button.png");
}

void MainMenuState::initMusicButton()
{
	this->musicButton.setSize({ 100.f, 100.f });
	this->musicButton.setPosition({ 0.f, resolution.height - this->musicButton.getGlobalBounds().height });
	if (musics.empty()) return;
	this->music = musics[rand() % musics.size()];

	this->music->setLoop(true);

	this->musicButton.setTexture(&this->textures["MUSIC_BUTTON"], true);
	this->currentMusicRect = sf::IntRect(0, 0, 100, 100);
	switch (this->buttonState)
	{
	case MusicBtnState::MAX:
		this->currentMusicRect.left = 0;
		this->music->setVolume(100.f);
		this->music->play();
		break;
	case MusicBtnState::LOWER:
		this->currentMusicRect.left = 100;
		this->music->setVolume(50.f);
		this->music->play();
		break;
	case MusicBtnState::OFF:
		this->currentMusicRect.left = 200;
		this->music->play();
		this->music->pause();
		break;
	}
	this->musicButton.setTextureRect(this->currentMusicRect);
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->resolution.width), static_cast<float>(this->resolution.height)));
	
	this->background.setTexture(&this->textures["BACKGROUND"]);
}

void MainMenuState::initButtons()
{	
	this->buttons["NEW_GAME_STATE"] = std::make_unique<gui::Button>(0.f, 0.f, 250.f, 50.f,
		&this->font, "New Game", 18,
		sf::Color(255, 255, 255), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["LOAD_GAME_STATE"] = std::make_unique<gui::Button>(0.f, 0.f, 250.f, 50.f,
		&this->font, "Load Game", 18,
		sf::Color(255, 255, 255), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS_STATE"] = std::make_unique<gui::Button>(0.f, 0.f, 250.f, 50.f,
		&this->font, "Settings", 18,
		sf::Color(255, 255, 255), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = std::make_unique<gui::Button>(0.f, 0.f, 250.f, 50.f,
		&this->font, "Quit", 18,
		sf::Color(255, 255, 255), sf::Color(255, 255, 255), sf::Color(255, 255, 255),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	//Positions all the buttons corectly after we create the Button objects so we can use the their size for positioning
	this->positionAllButtons();
}

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initFont();
	this->initTextures();
	this->initBackground();
	this->initButtons();
	this->loadSettings();
	this->loadMusics();
	this->initMusicButton();
}

MainMenuState::~MainMenuState()
{
	for (auto music : musics)
		delete music;
}

void MainMenuState::update()
{
	this->updateMousePositions();
	this->updateKeytime();
	this->updateInput();

	this->updateMusicButton();

	//Updating the buttons
	this->updateButtons();
}

void MainMenuState::render()
{
	this->window->draw(this->background);

	//Rendering the buttons
	for (auto& i : buttons)
		i.second->render(*this->window);

	this->window->draw(this->musicButton);
}
