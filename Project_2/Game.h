#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Entity.h"
#include "Ressources.h"
#include "Camera.h"

class Game
{
	sf::Vector2f m_screenSize;

	Camera m_camera;
	sf::View guiView;
	Ressource m_ressource;
	Player m_player = Player(m_ressource.getPlayerTexture(), m_ressource.getInventoryTexture(), m_ressource.getItemSelected());
	std::vector<Enemy*> m_orc;
	TileMap m_map;
	std::vector<Item*> m_groundItems;

	bool m_debugMode = false;

public:
	Game(sf::Vector2f screenSize = sf::Vector2f(0, 0));
	void load();
	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
	void keypressed(sf::Keyboard::Key keyCode);
};

