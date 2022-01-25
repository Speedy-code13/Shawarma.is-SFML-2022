	#pragma once
#include "Tile.h"
class TileMap
{
private:
	int gridSizeU;
	float gridSizeF;
	sf::Vector2i mapSize;
	std::vector< std::vector < Tile* > > map;
	sf::Texture tileSheet;

	int fromX;
	int fromY;
	int toX;
	int toY;
public:
	TileMap(float gridSize,  int width, int height);
	virtual ~TileMap();

	//Accessors
	sf::Texture* getTileSheet();

	void update(const sf::Vector2i playerPos, const sf::Vector2i view_size);
	void render(sf::RenderTarget& target);

};

