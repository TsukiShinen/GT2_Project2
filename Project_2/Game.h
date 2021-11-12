#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Point.h"

#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Entity.h"
#include "Ressources.h"

class Game
{
	Point m_screenSize;

	sf::View gameView;
	sf::View guiView;
	Ressource m_ressource;
	Player m_player = Player(m_ressource.getPlayerTexture(), m_ressource.getInventoryTexture(), m_ressource.getItemSelected());
	std::vector<Enemy*> m_orc;
	TileMap m_map;

	bool m_debugMode = false;

public:
	Game(Point screenSize = Point(0, 0));
	void load();
	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
	void keypressed(sf::Keyboard::Key keyCode);
};

