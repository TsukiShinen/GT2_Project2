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

    // Load the layer
    for (auto& layer : jsonTiled["layers"])
    {
        if (layer["type"] == "tilelayer") {
            // Create a new layer
            Layer newLayer;
            newLayer.name = layer["name"];
            newLayer.width = layer["width"];
            newLayer.height = layer["height"];
            newLayer.isVisible = layer["visible"];
            for (auto& property : layer["properties"]) {
                if (property["name"] == "level") {
                    newLayer.heightLevel = property["value"];
                }
                if (property["name"] == "playerBehind") {
                    newLayer.drawBeforePlayer = !property["value"];
                }
                if (property["name"] == "Collision") {
                    newLayer.isCollisionLayer = property["value"];
                }
            }
            m_lstCollisionCollider.emplace_back();
            for (size_t i = 0; i < layer["data"].size(); ++i)
            {
                if (newLayer.isCollisionLayer && layer["data"][i] != 0) {
                    sf::Vector2f pos = getTilePositionFromId(newLayer.width, i);
                    m_lstCollisionCollider[newLayer.heightLevel].push_back(sf::FloatRect(pos.x * m_tileWidth, pos.y * m_tileWidth, m_tileWidth, m_tileHeight));
                }
                newLayer.data.push_back(layer["data"][i]);
            }

            // Add the new layer
            m_layers.push_back(newLayer);
        }
        else if (layer["type"] == "objectgroup") 
        {
            for (auto& obj : layer["objects"]) {
                if (obj["name"] == "Player") {
                    m_startingPosition = sf::Vector2f(obj["x"], obj["y"]);
                }
                if (obj["name"] == "Orc") {
                    m_lstZoneEnemy.push_back(sf::IntRect(obj["x"], obj["y"], obj["width"], obj["height"]));
                }
                if (obj["type"] == "Level") {
                    HeightLevelCollider newRectLevel;
                    newRectLevel.rect = sf::FloatRect(obj["x"], obj["y"], obj["width"], obj["height"]);
                    newRectLevel.toLevel = obj["properties"][0]["value"];
                    m_lstHeightLevelCollider.push_back(newRectLevel);
                }
            }
        }
    }

    // Load the tileset
    size_t idTexture = 0;
    size_t lastTileId = 0;
    // Tile 0 is empty
    m_tileSets.tiles.emplace_back();
    for (auto& tileset : jsonTiled["tilesets"]) {
        // Load texture
        std::string imageName = tileset["image"];
        m_tileSets.textures.emplace_back(new sf::Texture); 
        if (!m_tileSets.textures[idTexture]->loadFromFile(PATH + imageName))
            std::cerr << "Can't load file: " << PATH + imageName << std::endl;
        // Load Tile of the texture
        for (auto& tile : tileset["tiles"])
        {
            Tile* newTile = new Tile();

            // Set the id
            newTile->id = lastTileId++;

            // Set the Texture (sprite)
            newTile->sprite.setTexture(*m_tileSets.textures[idTexture]);
            size_t c = tileset["columns"];
            size_t id = tile["id"];
            sf::Vector2f pos = getTilePositionFromId(c, id);
            newTile->sprite.setTextureRect(sf::IntRect(pos.x * m_tileWidth, pos.y * m_tileHeight, m_tileWidth, m_tileHeight));

            if (tile["animation"] > 0) { // Verify if something in it
                for (auto& anim : tile["animation"])
                {
                    TileAnimation newTileAnim;
                    sf::Vector2f animPos = getTilePositionFromId(tileset["columns"], anim["tileid"]);
                    newTileAnim.textureRect = sf::IntRect(animPos.x * m_tileWidth, animPos.y * m_tileHeight, m_tileWidth, m_tileHeight);
                    newTileAnim.duration = anim["duration"];
                    newTile->animation.push_back(newTileAnim);
                    m_animatedTile.push_back(newTile);
                }
            }

            m_tileSets.tiles.push_back(newTile);
        }
        idTexture++;
    }
}

TileMap::TileMap(std::string fileName)
{
    if (fileName == "") { return; }
	loadMap(fileName);
    std::cout << "Succefully charged tileMap : " << m_name << std::endl;
}

void TileMap::drawLayer(sf::RenderWindow& window, Layer& layer)
{
    for (size_t y = 0; y < layer.height; y++)
    {
        for (size_t x = 0; x < layer.width; x++)
        {
            if (layer.data[y * layer.width + x] != 0) {
                m_tileSets.tiles[layer.data[y * layer.width + x]]->sprite.setPosition(x * 8 , y * 8 );
                window.draw(m_tileSets.tiles[layer.data[y * layer.width + x]]->sprite);
                m_tileSets.tiles[layer.data[y * layer.width + x]]->sprite.setColor(sf::Color::White);
            }
        }
    }
}

void TileMap::drawBeforePlayer(sf::RenderWindow& window, int heightLevel, bool debugMode)
{
    if (m_name == "") { return; }
    for (auto& layer : m_layers)
    {
        if (layer.isVisible) {
            if (layer.drawBeforePlayer && layer.heightLevel <= heightLevel) {
                drawLayer(window, layer);
            }
        }
    }
}

void TileMap::drawAfterPlayer(sf::RenderWindow& window, int heightLevel, bool debugMode)
{
    if (m_name == "") { return; }
    for (auto& layer : m_layers)
    {
        if (layer.isVisible) {
            if (!layer.drawBeforePlayer || layer.heightLevel > heightLevel) {
                drawLayer(window, layer);
            }
        }
        else if (debugMode && heightLevel == layer.heightLevel) {
            drawLayer(window, layer);
        }
    }
}

void TileMap::update(sf::Time deltaTime) 
{
    if (m_name == "") { return; }
    for (Tile* tile : m_animatedTile) 
    {
        tile->animation[tile->currentAnim].chrono += deltaTime.asMilliseconds();
        if (tile->animation[tile->currentAnim].chrono >= tile->animation[tile->currentAnim].duration) {
            tile->animation[tile->currentAnim].chrono = 0;
            tile->sprite.setTextureRect(tile->animation[tile->currentAnim].textureRect);
            tile->currentAnim++;
            if (tile->currentAnim >= tile->animation.size()) {
                tile->currentAnim = 0;
            }
        }
    }
}

sf::Vector2f TileMap::getTilePositionFromId(size_t columns, size_t id) {
    return sf::Vector2f(id % columns, id / columns);
}