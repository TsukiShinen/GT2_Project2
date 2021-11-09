#include "Game.h"
#include "TileMap.h"

Game::Game(Point screenSize)
{
    m_screenSize = screenSize;
}

void Game::load()
{
   

    for (sf::RectangleShape& rectangle : listOfElement) {
        rectangle.setSize(sf::Vector2f(8, 8));
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(rand() % 200, rand() % 150);
    }

    m_map = TileMap("SandBox2.json");
    m_player.setPosition(m_map.getStartingPosition().toVector2());

    for (sf::IntRect* enemyZone : m_map.getEnemySpawn()) {
        m_orc.push_back(new Enemy(enemyZone));
    }

    gameView.setCenter(m_player.getPosition());
    gameView.setSize((m_screenSize/4).toVector2());
}

void Game::update(sf::Time& deltaTime)
{
    
    for (Enemy* enemy : m_orc) {
        enemy->update(deltaTime, m_player.getPosition());
    }
    m_map.update(deltaTime);
    m_player.update(deltaTime, m_map.getRectCollision(m_player.getMapLevel()));
    sf::Vector2f cameraPosition = m_player.getPosition();
    if (cameraPosition.y < 75) {
        cameraPosition.y = 75;
    }
    if (cameraPosition.x < 100) {
        cameraPosition.x = 100;
    }
    gameView.setCenter(cameraPosition);

    for (auto& rect : m_map.getRectLevel()) {
        if (m_player.collides(rect.rect)) {
            m_player.setMapLevel(rect.toLevel);
        }
    }
}

void Game::draw(sf::RenderWindow& window)
{
    window.setView(gameView);
    m_map.drawBeforePlayer(window, m_player.getMapLevel());

    
    m_player.draw(window);
    for (Enemy* enemy : m_orc) {
        enemy->draw(window, true);
    }

    m_map.drawAfterPlayer(window, m_player.getMapLevel());
    
}

void Game::keypressed(sf::Keyboard::Key keyCode)
{
    if (keyCode == sf::Keyboard::C) {
        m_map.changeShowDebug();
        m_player.changeShowDebug();
    }
    if (keyCode == sf::Keyboard::R) {
        m_map = TileMap("SandBox2.json");
    }
}
