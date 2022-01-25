
#include "pch.h"
#include "SettingsState.h"

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->loadSettings();
	this->initFonts();
    this->initBackground();
	this->initText();
	this->initGui();
}

SettingsState::~SettingsState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}	
	for (auto it = this->dropDownLists.begin(); it != this->dropDownLists.end(); ++it)
	{
		delete it->second;
	}
}

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
	this->activeElements["RESOLUTION"] = 0;
	this->activeElements["FRAMERATE"] = 0;
}

void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->resolution.width),
		static_cast<float>(this->resolution.height)
	)
	);
	this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/st.png");


	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	this->font.loadFromFile("Resources/Fonts/Dosis-Light.ttf");
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);

	this->optionsText.setCharacterSize(40);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString("Resolution        Vsync        Fullscreen        Framerate");

}

void SettingsState::updatePositions()
	{
		this->buttons["APPLY"]->setPosition(
			static_cast<float>(this->resolution.width) - this->buttons["APPLY"]->getGlobalBounds().width + 65.f,
			static_cast<float>(this->resolution.height) - this->buttons["APPLY"]->getGlobalBounds().height - 10.f
		);
		this->buttons["BACK"]->setPosition(
			static_cast<float>(this->resolution.width) - this->buttons["APPLY"]->getGlobalBounds().width - 165.f,
			static_cast<float>(this->resolution.height) - this->buttons["APPLY"]->getGlobalBounds().height - 15.f
		);
		this->optionsText.setPosition(
			{ static_cast<float>(this->resolution.width) / 2.f - this->optionsText.getGlobalBounds().width / 2.f,
			static_cast<float>(this->resolution.height) / 10.f
			});

		this->dropDownLists["RESOLUTION"]->setPosition(
			this->optionsText.getPosition().x,
			this->optionsText.getPosition().y + this->optionsText.getGlobalBounds().height + 10.f
		);

		this->dropDownLists["FRAMERATE"]->setPosition(
			this->optionsText.getPosition().x + this->optionsText.getGlobalBounds().width - 150.f,
			this->optionsText.getPosition().y + this->optionsText.getGlobalBounds().height + 10.f
		);

		this->buttons["FULLSCREEN"]->setPosition(
			this->optionsText.getPosition().x + this->optionsText.getGlobalBounds().width - 360.f,
			this->optionsText.getPosition().y + this->optionsText.getGlobalBounds().height + 10.f
		);

		this->buttons["VSYNC"]->setPosition(
			this->optionsText.getPosition().x + this->optionsText.getGlobalBounds().width - 540.f,
			this->optionsText.getPosition().y + this->optionsText.getGlobalBounds().height + 10.f
		);
	}

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button(
		0.f, 0.f, 250.f, 50.f,
		&this->font, "Back", 50,
		sf::Color(37, 41, 70), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	this->buttons["APPLY"] = new gui::Button(
		0.f, 0.f, 250.f, 50.f,
		&this->font, "Apply", 50,
		sf::Color(37, 41, 70), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
	
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(0.f, 0.f, 150.f, 50.f, this->font, modes_str.data(), modes_str.size(), this->activeElements["RESOLUTION"]);


	this->fps = { 240, 120, 60, 30 };

	std::vector<std::string> fps_str;
	for(auto &i : fps)
		fps_str.push_back(std::to_string(i) + "fps");
	
	this->dropDownLists["FRAMERATE"] = new gui::DropDownList(0.f, 0.f, 150.f, 50.f, this->font, fps_str.data(), fps_str.size(), this->activeElements["FRAMERATE"]);


	this->buttons["FULLSCREEN"] = new gui::Button(
		0.f, 0.f, 150.f, 50.f,
		&this->font, "Yes", 20,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);

	this->buttons["VSYNC"] = new gui::Button(
		0.f, 0.f, 150.f, 50.f,
		&this->font, "Yes", 20,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);

	if (this->stateData->gfx->fullscreen)
		this->buttons["FULLSCREEN"]->setText("Yes");
	else
		this->buttons["FULLSCREEN"]->setText("No");

	if (this->stateData->gfx->verticalSync)
		this->buttons["VSYNC"]->setText("Yes");
	else
		this->buttons["VSYNC"]->setText("No");

	this->dropDownLists["RESOLUTION"]->setActiveElementId(activeElements["RESOLUTION"]);
	this->dropDownLists["FRAMERATE"]->setActiveElementId(activeElements["FRAMERATE"]);

	this->updatePositions();
}

void SettingsState::endState()
{
	this->saveSettings();
	this->quit = true;
}

void SettingsState::loadSettings()
{
	std::ifstream ifs("Config/settings_state.ini");
	if (ifs.is_open())
	{
		ifs >> activeElements["RESOLUTION"];
		ifs >> activeElements["FRAMERATE"];
		ifs.close();
	}
}

void SettingsState::saveSettings()
{
	std::ofstream ofs("Config/settings_state.ini");
	if (ofs.is_open())
	{
		ofs << activeElements["RESOLUTION"] << "\n";
		ofs << activeElements["FRAMERATE"] << "\n";
		ofs.close();
	}
}

void SettingsState::updateResolution()
{
	this->updatedRes = true;
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->resolution.width),
		static_cast<float>(this->resolution.height)
	)
	);
	this->updatePositions();
}

void SettingsState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeytime())
	{
		this->endState();
	}
}

void SettingsState::updateGui(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Quit Game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	//Applies selected settings
	else if (this->buttons["APPLY"]->isPressed())
	{
		auto resolutionModeIndex = this->dropDownLists["RESOLUTION"]->getActiveElementId();
		auto framerateIndex = this->dropDownLists["FRAMERATE"]->getActiveElementId();

		this->activeElements["RESOLUTION"] = resolutionModeIndex;
		this->activeElements["FRAMERATE"] = framerateIndex;

		this->stateData->gfx->resolution = this->modes[resolutionModeIndex];
		this->stateData->gfx->framerateLimit = this->fps[framerateIndex];

		bool isMaxResolution = resolutionModeIndex == 0;

		this->stateData->gfx->updateWindow(this->window, isMaxResolution);
		this->updateResolution();
	}
	//Update Vsync button
	else if (this->buttons["VSYNC"]->isPressed() && this->getKeytime())
	{
		if (this->stateData->gfx->verticalSync)
		{
			this->stateData->gfx->verticalSync = false;
			this->buttons["VSYNC"]->setText("No");
		}
		else
		{
			this->stateData->gfx->verticalSync = true;
			this->buttons["VSYNC"]->setText("Yes");
		}
	}
	//Update fullscreen button
	else if  (this->buttons["FULLSCREEN"]->isPressed() && this->getKeytime())
	{
		if (this->stateData->gfx->fullscreen)
		{
			this->stateData->gfx->fullscreen = false;
			this->buttons["FULLSCREEN"]->setText("No");
		}
		else
		{
			this->stateData->gfx->fullscreen = true;
			this->buttons["FULLSCREEN"]->setText("Yes");
		}
	}

	//Drop down lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, dt);
	}

}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::update()
{
	this->updateMousePositions();
	this->updateKeytime();	
	this->updateInput(*this->dt);

	this->updateGui(*this->dt);
}	

void SettingsState::render()
{
	this->window->draw(this->background);

	this->renderGui(*this->window);

	this->window->draw(this->optionsText);


}

