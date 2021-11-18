#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "json.h"
using json = nlohmann::json;

class TileMap
{
	const std::string PATH = "./Assets/Map/";
	const size_t TILE_SIZE = 8;

	struct Layer {
		std::string name{ ""};
		std::vector<size_t> data;
		size_t width{ 0 };
		size_t height{ 0 };
		int heightLevel = 0;
		bool drawBeforePlayer = true;
		bool isCollisionLayer = false;

		bool isVisible = true;
	};

	struct TileAnimation {
		sf::IntRect textureRect;
		size_t duration{ 1 };
		float chrono = 0;
	};

	struct Tile {
		size_t id{ 0 };
		sf::Sprite sprite;
		int currentAnimationFrame = 0;

		std::vector<TileAnimation> lstFrameAnimation;
	};

	struct TileSet {
		std::vector<Tile*> tiles;
		std::vector<sf::Texture*> textures;
	};

	struct HeightLevelCollider {
		sf::FloatRect rect{ 0, 0, 0, 0 };
		int toLevel{ 0 };
	};
public:
	TileMap(std::string fileName = "");

	sf::Vector2f getStartingPosition() { return m_startingPosition; }
	size_t getWidth() { return m_width * TILE_SIZE; }
	size_t getHeight() { return m_height * TILE_SIZE; }
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
	void loadMapInfo(const json& mapJson);
	void loadLayers(const json& mapJson);
	void loadTileLayer(const json& layerJson);
	void loadLayerInfoTo(Layer& layer, const json& layerJson);
	void loadLayerPropertiesTo(Layer& layer, const json& layerJson);
	void loadLayerDataTo(Layer& layer, const json& layerJson);
	void loadObjectLayer(const json& layerJson);
	void loadTileSets(const json& mapJson);
	void loadTileSetTextures(const json& mapJson);
	void loadTileSetTiles(const json& tile);
	void loadTileAnimationTo(Tile* tile, const json& mapJson, const size_t tileSetwidth);

	sf::Vector2f getTilePositionFromId(size_t columns, size_t id);

	void drawLayer(sf::RenderWindow& window, Layer& layer);
};
