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
		bool isSolid = false;
		int currentAnim = 0;

		std::vector<TileAnimation> animation;
	};

	struct TileSet {
		std::vector<Tile*> tiles;
		std::vector<sf::Texture*> textures;
	};

	const std::string PATH = "./Assets/Map/";
	const size_t SCALE = 1;

	std::string m_name;

	size_t m_height = 0;
	size_t m_width = 0;
	size_t m_tileHeight = 0;
	size_t m_tileWidth = 0;

	std::vector<Layer> m_layers;
	TileSet m_tileSet;
	std::vector<Tile*> m_animatedTile;

	Point m_startingPosition;

	bool m_showCollsion = false;

	void loadMap(std::string fileName);
public:
	TileMap(std::string fileName);

	Point getStartingPosition() { return m_startingPosition; }

	void draw(sf::RenderWindow& window);

	void update(sf::Time deltaTime);

	void changeShowDebug();
};
