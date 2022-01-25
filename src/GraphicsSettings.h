#pragma once
class GraphicsSettings
{
private:
	bool iconLoaded;
public:
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	unsigned framerateLimit;
	bool verticalSync;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;
	sf::Image icon;
public:
	GraphicsSettings();
	//Functions
	void saveToFile(const std::string& path);
	void loadFromFile(const std::string& path);
	void updateWindow(std::shared_ptr<sf::RenderWindow> window, bool isMaxResolution);
	void setIcon(std::shared_ptr<sf::RenderWindow> window);
};