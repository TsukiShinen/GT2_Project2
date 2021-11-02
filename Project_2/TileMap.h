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

	const std::string PATH = "./Assets/Map/";

	std::string m_name;

	size_t m_height = 0;
	size_t m_width = 0;
	size_t m_tileHeight = 0;
	size_t m_tileWidth = 0;

	std::vector<Layer> m_layers;

	void loadMap(std::string fileName);
public:
	TileMap(std::string fileName);
};
