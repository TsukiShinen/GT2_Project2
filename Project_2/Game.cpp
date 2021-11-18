#include "Game.h"
#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include <functional>

Game::Game(sf::Vector2f screenSize)
{
    m_screenSize = screenSize;
}

void Game::load()
{
    m_ressource.load();

    m_map = TileMap("Lvl_1.json");
    m_player.setPosition(m_map.getStartingPosition()    );

    for (sf::IntRect& enemyZone : m_map.getEnemyZone()) {
        m_orc.push_back(new Enemy(enemyZone, m_ressource.getOrcTexture(), m_ressource.getlifeBarTexture()));
    }
    ProgressBar progressBar(0.f, 10.f, sf::Sprite(*m_ressource.getHeart()), new sf::Sprite(*m_ressource.getHeartBackground()));
    m_player.setProgressBar(progressBar);

    guiView.setCenter(100, 75);
    guiView.setSize(m_screenSize / 4.f);
    m_camera.setView(sf::View(m_player.getPosition(), m_screenSize / 4.f));
}

void Game::update(sf::Time& deltaTime)
{
    if (!m_player.isAlive()) { // Update only player (for animation if dead)
        m_player.update(deltaTime, m_map.getCollisionColliders(m_player.getMapLevel()));
        return;
    }

    // Player update
    m_player.update(deltaTime, m_map.getCollisionColliders(m_player.getMapLevel()));
    for (auto& rect : m_map.getHeightLevelColliders()) { // Check collision for Height level
        if (m_player.collides(rect.rect)) {
            m_player.setMapLevel(rect.toLevel);
        }
    }
    for (int i = static_cast<int>(m_groundItems.size() - 1); i >= 0; --i) { // Pick item
        if (m_player.collides(m_groundItems[i]->getBoundingBox())) {
            bool getItem = m_player.pickItem(m_groundItems[i]);
            if (getItem) {
                m_groundItems.erase(m_groundItems.begin() + i);
            }
        }
    }

    // Enemy Update
    for (Enemy* enemy : m_orc) {
        enemy->update(deltaTime, m_player.getPosition());
        if (enemy->isAlive()) {
            if (m_player.isAttacking(enemy->getPosition()))
            {
                enemy->takeDamage(m_player.getDamage(), deltaTime, m_player.getAttackSpeed());
                sf::Vector2f enemyPos = enemy->getCenter();
                sf::Vector2f playerPos = m_player.getCenter();
                double angle = Utils::angle(playerPos, enemyPos);
                sf::Vector2f force(cos(angle), sin(angle));
                force = Utils::normalize(force) * 5000.f;
                enemy->addForce(force);
            }
            // Collision with player
            if (m_player.collides(enemy->getBoundingBox()) && enemy->isAlive()) {
                sf::Vector2f enemyPos = enemy->getCenter();
                sf::Vector2f playerPos = m_player.getCenter();
                double angle = Utils::angle(enemyPos, playerPos);
                sf::Vector2f force(cos(angle), sin(angle));
                force = Utils::normalize(force) * 5000.f;
                m_player.addForce(force);
                m_player.takeDamage(1.f);
            }
        }
    }

    // Update Map (animation)
    m_map.update(deltaTime);

    // Update Camera
    sf::Vector2f cameraPosition = m_player.getPosition();
    if (cameraPosition.y < 75) {
        cameraPosition.y = 75;
    }
    if (cameraPosition.x < 100) {
        cameraPosition.x = 100;
    }
    if (cameraPosition.y > m_map.getHeight()-75) {
        cameraPosition.y = m_map.getHeight() - 75;
    }
    if (cameraPosition.x > m_map.getWidth() - 100) {
        cameraPosition.x = m_map.getWidth() - 100;
    }
    m_camera.Follow(deltaTime, cameraPosition);

    // Remove dead Enemy
    for (int i = static_cast<int>(m_orc.size() - 1); i >= 0; --i) {
        if (m_orc[i]->toRemove()) {
            Enemy* enemy = m_orc[i];

            m_groundItems.push_back(new Item("Meat", m_ressource.getMeat(), Item::Type::Potion, m_player.heal));
            m_groundItems[m_groundItems.size() - 1]->setPosition(enemy->getPosition());

            m_orc.erase(m_orc.begin() + i);
            delete enemy;
        }
    }
}

void Game::draw(sf::RenderWindow& window)
{
    // Game
    window.setView(m_camera.getView());
    m_map.drawBeforePlayer(window, m_player.getMapLevel(), m_debugMode);

    for (Item* item : m_groundItems) {
        item->drawIcon(window, m_debugMode);
    }

    for (Enemy* enemy : m_orc) {
        enemy->draw(window, m_debugMode);
    }

    m_player.draw(window, m_debugMode);
    
    m_map.drawAfterPlayer(window, m_player.getMapLevel(), m_debugMode);

    // GUI
    window.setView(guiView);
    m_player.drawUI(window, m_debugMode);
}

void Game::keypressed(sf::Keyboard::Key keyCode)
{
    if (keyCode == sf::Keyboard::C) {
        m_debugMode = !m_debugMode;
    }
    if (keyCode == sf::Keyboard::R) {
        m_map = TileMap("Lvl_1.json");
    }
    if (keyCode == sf::Keyboard::T) {
        m_player.addForce(sf::Vector2f(2000, 2000));
    }
    if (keyCode == sf::Keyboard::P) {
        for (Enemy* enemy : m_orc) {
            enemy->takeDamage(2);
        }
    }
    m_player.keypressed(keyCode);
    
}
