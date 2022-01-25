#include "pch.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	this->title = "Shawarma.is";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->framerateLimit = 120;
	this->verticalSync = false;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();

	if (this->icon.loadFromFile("Resources/Images/Players/shaorma.png"))
	{
		this->iconLoaded = true;
	}
}

void GraphicsSettings::saveToFile(const std::string& path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->title << "\n";
		ofs << this->resolution.width << " " << this->resolution.height << "\n";
		ofs << this->fullscreen << "\n";
		ofs << this->framerateLimit << "\n";
		ofs << this->verticalSync << "\n";
		ofs << this->contextSettings.antialiasingLevel << "\n";
		ofs.close();
	}

}

void GraphicsSettings::loadFromFile(const std::string& path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->framerateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
		ifs.close();
	}
}

void GraphicsSettings::updateWindow(std::shared_ptr<sf::RenderWindow> window, bool isMaxResolution)
{
	if (this->fullscreen)
	{
		window->create(this->resolution, this->title, sf::Style::Fullscreen, this->contextSettings);
	}
	else
	{
		window->create(this->resolution, this->title, sf::Style::Default, this->contextSettings);
		if(isMaxResolution)
			ShowWindow(window->getSystemHandle(), SW_MAXIMIZE);
	}

	this->setIcon(window);

	window->setVerticalSyncEnabled(this->verticalSync);
	window->setFramerateLimit(this->framerateLimit);
}

void GraphicsSettings::setIcon(std::shared_ptr<sf::RenderWindow> window)
{
	if (this->iconLoaded)
		window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}
