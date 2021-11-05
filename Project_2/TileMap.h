#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

struct Point;

class TileMap
{
	struct Layer {
		size_t id;
		std::string name;
		std::vector<size_t> data;
		size_t width;
		size_t height;

		bool isVisible;
	};

	struct TileAnimation {
		sf::IntRect rect;
		size_t duration;
		float time = 0;
	};

	struct Tile {
		size_t id;
		sf::Sprite sprite;
		int currentAnim = 0;

		std::vector<TileAnimation> animation;
	};

	struct TileSets {
		std::vector<Tile*> tiles;
		std::vector<sf::Texture*> textures;
	};

	const std::string PATH = "./Assets/Map/";
	size_t m_scale = 1;

	std::string m_name = "";

	size_t m_height = 0;
	size_t m_width = 0;
	size_t m_tileHeight = 0;
	size_t m_tileWidth = 0;

	std::vector<Layer> m_layers;
	TileSets m_tileSet;
	std::vector<Tile*> m_animatedTile;

	Point m_startingPosition;

	void loadMap(std::string fileName);
public:
	TileMap(std::string fileName = "");

	Point getStartingPosition() { return m_startingPosition; }

	void draw(sf::RenderWindow& window);

	void update(sf::Time deltaTime);

	void changeShowDebug();

	// move assignment
	TileMap& operator=(TileMap&& other) noexcept
	{
		if (this == &other) { return *this; }

		m_scale = 1;

		m_name = other.m_name;

		m_height = other.m_height;
		m_width = other.m_width;
		m_tileHeight = other.m_tileHeight;
		m_tileWidth = other.m_tileWidth;

		m_layers = other.m_layers;
		m_tileSet = other.m_tileSet;
		m_animatedTile = other.m_animatedTile;

		m_startingPosition = other.m_startingPosition;

		return *this;
	}
};
