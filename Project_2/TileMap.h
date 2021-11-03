#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

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

	struct Tile {
		size_t id;
		sf::Sprite sprite;
		bool isSolid = false;
	};

	struct TileSet {
		std::vector<Tile> tiles;
		std::vector<sf::Texture*> textures;
	};

	const std::string PATH = "./Assets/Map/";
	const size_t SCALE = 4;

	std::string m_name;

	size_t m_height = 0;
	size_t m_width = 0;
	size_t m_tileHeight = 0;
	size_t m_tileWidth = 0;

	std::vector<Layer> m_layers;
	TileSet m_tileSet;

	bool m_showCollsion = false;

	void loadMap(std::string fileName);
public:
	TileMap(std::string fileName);

	void draw(sf::RenderWindow& window);

	void changeShowDebug() { m_showCollsion = !m_showCollsion; }
};
