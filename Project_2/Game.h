#pragma once
#include <SFML/Graphics.hpp>

#include "Point.h"

#include "Player.h"
#include "TileMap.h"

class Game
{
	Point m_screenSize;

	sf::View gameView;

	Player m_player;
	sf::Texture pTexture;
	TileMap m_map;
	std::vector<sf::RectangleShape> listOfElement{ 10 };

public:
	Game(Point screenSize = Point(0, 0));
	void load();
	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
	void keypressed(sf::Keyboard::Key keyCode);
};

