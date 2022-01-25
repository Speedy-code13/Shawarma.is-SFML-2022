#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, int width, int height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<int>(gridSize);
	this->mapSize.x = width;
	this->mapSize.y = height;
	
	this->tileSheet.loadFromFile("Resources/Images/Map/download.jpg");	
	this->map.resize(this->mapSize.x, std::vector<Tile*>());
	for (int x = 0; x < this->mapSize.x; x++)
	{
		for (int	y = 0; y < this->mapSize.y; y++)
		{
			this->map[x].resize(this->mapSize.y);
			this->map[x][y] = new Tile(x * gridSizeF, y * gridSizeF, gridSizeF, tileSheet);
		}
	}
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
}	

TileMap::~TileMap()
{
	for (int x = 0; x < this->mapSize.x; x++)
	{
		for (int y = 0; y < this->mapSize.y; y++)
		{
				delete this->map[x][y];
		}
	}
}

sf::Texture* TileMap::getTileSheet()
{
	return &this->tileSheet;
}

void TileMap::update(const sf::Vector2i playerPos, const sf::Vector2i view_size)
{
	this->fromX = playerPos.x - view_size.x -1;
	this->toX = playerPos.x + view_size.x + 1;
	this->fromY = playerPos.y - view_size.y - 1;
	this->toY = playerPos.y + view_size.y + 1;

	//X
	if (fromX < 0)
		fromX = 0;
	else if (fromX >= mapSize.x)
		fromX = mapSize.x ;

	if (toX < 0)
		toX = 0;
	else if (toX >= mapSize.x)
		toX = mapSize.x ;

	//Y
	if (fromY < 0)
		fromY = 0;
	else if (fromY >= mapSize.y)
		fromY = mapSize.y;

	if (toY < 0)
		toY = 0;
	else if (toY >= mapSize.y)
		toY = mapSize.y ;
}

void TileMap::render(sf::RenderTarget& target)
{
	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{
			this->map[x][y]->render(target);
		}
	}
}

