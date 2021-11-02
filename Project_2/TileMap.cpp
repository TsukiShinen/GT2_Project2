#include <fstream>
#include <iostream>

#include "TileMap.h"

#include "json.h"

using json = nlohmann::json;

void TileMap::loadMap(std::string fileName)
{
    json jsonTiled;

    // Read the json file
    std::ifstream reader(PATH + fileName);
    reader >> jsonTiled;
    reader.close();

    // Get the info fromo the json
    m_name = fileName.substr(0, fileName.find(".")); // get the name from the file name (splt on .)

    m_height = jsonTiled["height"];
    m_width = jsonTiled["width"];
    m_tileHeight = jsonTiled["tileheight"];
    m_tileWidth = jsonTiled["tilewidth"];

    for (auto &layer : jsonTiled["layers"])
    {
        // Create a new layer
        Layer newLayer;
        newLayer.id = layer["id"];
        newLayer.name = layer["name"];
        newLayer.width = layer["width"];
        newLayer.height = layer["height"];
        newLayer.isVisible = layer["visible"];
        for (auto& id : layer["data"]) {
            newLayer.data.push_back(id);
        }

        // Add the new layer
        m_layers.push_back(newLayer);
    }
}

TileMap::TileMap(std::string fileName)
{
	loadMap(fileName);

    std::cout << "Succefully charged tileMap : " << m_name << std::endl;
    std::cout << "Width : " << m_width << std::endl;
    std::cout << "Height : " << m_height << std::endl;

    std::cout << std::endl;
    for (auto &layer : m_layers)
    {
        std::cout << "Layer : " << layer.name << std::endl;

        for (size_t y = 0; y < layer.height; y++)
        {
            for (size_t x = 0; x < layer.width; x++)
            {
                std::cout << layer.data[y * layer.width + x] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
