#include <fstream>
#include <iostream>
#include "Point.h"

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

    // Load the layer
    for (auto& layer : jsonTiled["layers"])
    {
        if (layer["type"] == "tilelayer") {
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
        else if (layer["type"] == "objectgroup") 
        {
            for (auto& obj : layer["objects"]) {
                if (obj["name"] == "Player") {
                    m_startingPosition = Point(obj["x"], obj["y"]);
                }
                if (obj["name"] == "Orc") {
                    m_enemySpawn.push_back(new sf::IntRect(obj["x"], obj["y"], obj["width"], obj["height"]));
                }
            }
        }
    }

    // Load the tileset
    size_t idTexture = 0;
    size_t lastTileId = 0;
    // Tile 0 is empty
    m_tileSet.tiles.emplace_back();
    for (auto& tileset : jsonTiled["tilesets"]) {
        // Load texture
        std::string imageName = tileset["image"];
        m_tileSet.textures.emplace_back(new sf::Texture); 
        if (!m_tileSet.textures[idTexture]->loadFromFile(PATH + imageName))
            std::cerr << "Can't load file: " << PATH + imageName << std::endl;
        // Load Tile of the texture
        for (auto& tile : tileset["tiles"])
        {
            Tile* newTile = new Tile();

            // Set the id
            newTile->id = lastTileId++;

            // Set the Texture (sprite)
            newTile->sprite.setTexture(*m_tileSet.textures[idTexture]);
            newTile->sprite.setScale(m_scale, m_scale);
            size_t c = tileset["columns"];
            size_t x = tile["id"] % c;
            size_t y = 0;
            if (x != 0) 
            {
                y = tile["id"] / c;
            }
            newTile->sprite.setTextureRect(sf::IntRect(x * m_tileWidth, y * m_tileHeight, m_tileWidth, m_tileHeight));

            if (tile["animation"] > 0) { // Verify if something in it
                for (auto& anim : tile["animation"])
                {
                    TileAnimation newTileAnim;
                    size_t animX = anim["tileid"] % c;
                    size_t animY = anim["tileid"] / c;
                    newTileAnim.rect = sf::IntRect(animX * m_tileWidth, animY * m_tileHeight, m_tileWidth, m_tileHeight);
                    newTileAnim.duration = anim["duration"];
                    newTile->animation.push_back(newTileAnim);
                    m_animatedTile.push_back(newTile);
                }
            }

            m_tileSet.tiles.push_back(newTile);
        }
        idTexture++;
    }
}

TileMap::TileMap(std::string fileName)
{
    if (fileName == "") { return; }
	loadMap(fileName);
    std::cout << m_enemySpawn[0];
    std::cout << "Succefully charged tileMap : " << m_name << std::endl;
}

void TileMap::draw(sf::RenderWindow& window)
{
    if (m_name == "") { return; }
    for (auto& layer : m_layers)
    {
        if (layer.isVisible) {
            for (size_t y = 0; y < layer.height; y++)
            {
                for (size_t x = 0; x < layer.width; x++)
                {
                    if (layer.data[y * layer.width + x] != 0) {
                        m_tileSet.tiles[layer.data[y * layer.width + x]]->sprite.setPosition(x * 8 * m_scale, y * 8 * m_scale);
                        window.draw(m_tileSet.tiles[layer.data[y * layer.width + x]]->sprite);
                        m_tileSet.tiles[layer.data[y * layer.width + x]]->sprite.setColor(sf::Color::White);
                    }
                }
            }
        }
    }
}

void TileMap::update(sf::Time deltaTime) 
{
    if (m_name == "") { return; }
    for (Tile* tile : m_animatedTile) 
    {
        tile->animation[tile->currentAnim].time += deltaTime.asMilliseconds();
        if (tile->animation[tile->currentAnim].time >= tile->animation[tile->currentAnim].duration) {
            tile->animation[tile->currentAnim].time = 0;
            tile->sprite.setTextureRect(tile->animation[tile->currentAnim].rect);
            tile->currentAnim++;
            if (tile->currentAnim >= tile->animation.size()) {
                tile->currentAnim = 0;
            }
        }
    }
}

void TileMap::changeShowDebug()
{
    for (auto& layer : m_layers)
    {
        if (layer.name == "Collision") {
            layer.isVisible = !layer.isVisible;
        }
    }
}