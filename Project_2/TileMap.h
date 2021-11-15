#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class TileMap
{
	const std::string PATH = "./Assets/Map/";

	struct Layer {
		std::string name;
		std::vector<size_t> data;
		size_t width;
		size_t height;
		int heightLevel = 0;
		bool drawBeforePlayer = true;
		bool isCollisionLayer = false;

		bool isVisible;
	};

	struct TileAnimation {
		sf::IntRect textureRect;
		size_t duration;
		float chrono = 0;
	};

	struct Tile {
		size_t id;
		sf::Sprite sprite;
		int currentAnim = 0;

		std::vector<TileAnimation> animation;
	};

	struct TileSet {
		std::vector<Tile*> tiles;
		std::vector<sf::Texture*> textures;
	};

	struct HeightLevelCollider {
		sf::FloatRect rect;
		int toLevel;
	};
public:
	TileMap(std::string fileName = "");

	sf::Vector2f getStartingPosition() { return m_startingPosition; }
	std::vector<sf::IntRect>& getEnemyZone() { return m_lstZoneEnemy; }
	std::vector<sf::FloatRect>& getCollisionColliders(int level) { return m_lstCollisionCollider[level]; }
	std::vector<HeightLevelCollider>& getHeightLevelColliders() { return m_lstHeightLevelCollider; }

	void drawBeforePlayer(sf::RenderWindow& window, int level, bool debugMode);
	void drawAfterPlayer(sf::RenderWindow& window, int level, bool debugMode);

	void update(sf::Time deltaTime);

	// move assignment
	TileMap& operator=(TileMap&& other) noexcept
	{
		if (this == &other) { return *this; }

		m_name = other.m_name;

		m_height = other.m_height;
		m_width = other.m_width;
		m_tileHeight = other.m_tileHeight;
		m_tileWidth = other.m_tileWidth;

		m_layers = other.m_layers;
		m_tileSets = other.m_tileSets;
		m_animatedTile = other.m_animatedTile;

		m_startingPosition = other.m_startingPosition;
		m_lstZoneEnemy = other.m_lstZoneEnemy;
		m_lstCollisionCollider = other.m_lstCollisionCollider;
		m_lstHeightLevelCollider = other.m_lstHeightLevelCollider;


		return *this;
	}

public:
	std::string m_name = "";

	size_t m_height = 0;
	size_t m_width = 0;
	size_t m_tileHeight = 0;
	size_t m_tileWidth = 0;

	std::vector<Layer> m_layers;
	TileSet m_tileSets;
	std::vector<Tile*> m_animatedTile;
	std::vector<std::vector<sf::FloatRect>> m_lstCollisionCollider;
	std::vector<HeightLevelCollider> m_lstHeightLevelCollider;

	sf::Vector2f m_startingPosition;
	std::vector<sf::IntRect> m_lstZoneEnemy;

	void loadMap(std::string fileName);
	sf::Vector2f getTilePositionFromId(size_t columns, size_t id);

	void drawLayer(sf::RenderWindow& window, Layer& layer);
};
