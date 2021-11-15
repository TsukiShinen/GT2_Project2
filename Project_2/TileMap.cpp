#include <fstream>
#include <iostream>

#include "TileMap.h"
#include "Utils.h"

#include "json.h"
using json = nlohmann::json;

void TileMap::loadMap(std::string fileName)
{
    json jsonTiled = Utils::readJson(PATH + fileName);

    m_name = fileName.substr(0, fileName.find("."));
    loadMapInfo(jsonTiled);

    loadLayers(jsonTiled);

    loadTileSets(jsonTiled);
}

void TileMap::loadMapInfo(const json& mapJson)
{
    m_height = mapJson["height"];
    m_width = mapJson["width"];
    m_tileHeight = mapJson["tileheight"];
    m_tileWidth = mapJson["tilewidth"];
}

void TileMap::loadLayers(const json& mapJson)
{
    for (auto& layer : mapJson["layers"])
    {
        if (layer["type"] == "tilelayer") {
            loadTileLayer(layer);
        }
        else if (layer["type"] == "objectgroup")
        {
            loadObjectLayer(layer);
        }
    }
}

void TileMap::loadTileLayer(const json& layerJson)
{
    Layer newLayer;
    loadLayerInfoTo(newLayer, layerJson);
    loadLayerPropertiesTo(newLayer, layerJson);
    loadLayerDataTo(newLayer, layerJson);

    m_layers.push_back(newLayer);
}


void TileMap::loadLayerInfoTo(Layer& layer, const json& layerJson) {
    layer.name = layerJson["name"];
    layer.width = layerJson["width"];
    layer.height = layerJson["height"];
    layer.isVisible = layerJson["visible"];
}

void TileMap::loadLayerPropertiesTo(Layer& layer, const json& layerJson) {
    for (auto& property : layerJson["properties"]) {
        if (property["name"] == "level") {
            layer.heightLevel = property["value"];
        }
        else if (property["name"] == "playerBehind") {
            layer.drawBeforePlayer = !property["value"];
        }
        else if (property["name"] == "Collision") {
            layer.isCollisionLayer = property["value"];
        }
    }
}

void TileMap::loadLayerDataTo(Layer& layer, const json& layerJson) {
    m_lstCollisionCollider.emplace_back();
    for (size_t i = 0; i < layerJson["data"].size(); ++i) {
        if (layer.isCollisionLayer && layerJson["data"][i] != 0) {
            sf::Vector2f pos = getTilePositionFromId(layer.width, i);
            m_lstCollisionCollider[layer.heightLevel].push_back(sf::FloatRect(pos.x * m_tileWidth, pos.y * m_tileWidth, m_tileWidth, m_tileHeight));
        }
        layer.data.push_back(layerJson["data"][i]);
    }
}

void TileMap::loadObjectLayer(const json& layerJson)
{
    for (auto& obj : layerJson["objects"]) {
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

void TileMap::loadTileSets(const json& mapJson)
{
    // Load the tileset
    size_t idTexture = 0;
    size_t lastTileId = 0;
    // Tile 0 is empty
    m_tileSets.tiles.emplace_back();
    for (auto& tileset : mapJson["tilesets"]) {
        // Load texture
        std::string imageName = tileset["image"];
        m_tileSets.textures.emplace_back(new sf::Texture);
        if (!m_tileSets.textures[idTexture]->loadFromFile(PATH + imageName))
            std::cerr << "Can't load file: " << PATH + imageName << std::endl;
        // Load Tile of the texture
        loadTileSetTiles(tileset);
        idTexture++;
    }
}

void TileMap::loadTileSetTextures(const json& mapJson)
{
}

void TileMap::loadTileSetTiles(const json& tileSetJson)
{
    for (auto& tile : tileSetJson["tiles"])
    {
        Tile* newTile = new Tile();

        // Set the id
        newTile->id = tileSetJson["firstgid"];
        newTile->id += tile["id"];

        // Set the Texture (sprite)
        newTile->sprite.setTexture(*m_tileSets.textures[m_tileSets.textures.size()-1]);
        size_t c = tileSetJson["columns"];
        size_t id = tile["id"];
        sf::Vector2f pos = getTilePositionFromId(c, id);
        newTile->sprite.setTextureRect(sf::IntRect(pos.x * m_tileWidth, pos.y * m_tileHeight, m_tileWidth, m_tileHeight));

        loadTileAnimationTo(newTile, tile, c);

        m_tileSets.tiles.push_back(newTile);
    }
}

void TileMap::loadTileAnimationTo(Tile* tile, const json& tileJson, const size_t tileSetwidth)
{
    if (tileJson.find("animation") != tileJson.end()) { // Verify if something in it
        for (auto& anim : tileJson["animation"])
        {
            TileAnimation newTileAnim;
            sf::Vector2f animPos = getTilePositionFromId(tileSetwidth, anim["tileid"]);
            newTileAnim.textureRect = sf::IntRect(animPos.x * m_tileWidth, animPos.y * m_tileHeight, m_tileWidth, m_tileHeight);
            newTileAnim.duration = anim["duration"];
            tile->lstFrameAnimation.push_back(newTileAnim);
            m_animatedTile.push_back(tile);
        }
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
        tile->lstFrameAnimation[tile->currentAnimationFrame].chrono += deltaTime.asMilliseconds();
        if (tile->lstFrameAnimation[tile->currentAnimationFrame].chrono >= tile->lstFrameAnimation[tile->currentAnimationFrame].duration) {
            tile->lstFrameAnimation[tile->currentAnimationFrame].chrono = 0;
            tile->sprite.setTextureRect(tile->lstFrameAnimation[tile->currentAnimationFrame].textureRect);
            tile->currentAnimationFrame++;
            if (tile->currentAnimationFrame >= tile->lstFrameAnimation.size()) {
                tile->currentAnimationFrame = 0;
            }
        }
    }
}

sf::Vector2f TileMap::getTilePositionFromId(size_t columns, size_t id) {
    return sf::Vector2f(id % columns, id / columns);
}