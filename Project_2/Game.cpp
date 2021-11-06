#include "Game.h"
#include "TileMap.h"

Game::Game(Point screenSize)
{
    m_screenSize = screenSize;
}

void Game::load()
{
    pTexture;
    pTexture.loadFromFile("./Assets/PlayerAnimations.png");
    m_player.setTexture(pTexture);
    m_player.setTextureRect(sf::IntRect(0, 352, 32, 32));

    for (sf::RectangleShape& rectangle : listOfElement) {
        rectangle.setSize(sf::Vector2f(8, 8));
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(rand() % 200, rand() % 150);
    }

    m_map = TileMap("SandBox2.json");
    m_player.setPosition(m_map.getStartingPosition().toVector2());

    std::cout << m_map.getEnemySpawn().size() << std::endl;
    for (sf::IntRect* enemyZone : m_map.getEnemySpawn()) {
        std::cout << enemyZone->top << std::endl;
        m_orc.push_back(new Enemy(enemyZone));
    }

    gameView.setCenter(m_player.getPosition());
    gameView.setSize((m_screenSize/4).toVector2());
}

void Game::update(sf::Time& deltaTime)
{
    m_player.update(deltaTime, listOfElement);
    for (Enemy* enemy : m_orc) {
        enemy->update(deltaTime);
    }
    m_map.update(deltaTime);

    sf::Vector2f cameraPosition = m_player.getPosition();
    if (cameraPosition.y < 75) {
        cameraPosition.y = 75;
    }
    if (cameraPosition.x < 100) {
        cameraPosition.x = 100;
    }
    gameView.setCenter(cameraPosition);
}

void Game::draw(sf::RenderWindow& window)
{
    window.setView(gameView);
    m_map.draw(window);
    window.draw(m_player);
    for (Enemy* enemy : m_orc) {
        enemy->draw(window);
    }
    for (sf::RectangleShape rectangle : listOfElement) {
        window.draw(rectangle);
    }
}

void Game::keypressed(sf::Keyboard::Key keyCode)
{
    if (keyCode == sf::Keyboard::C) {
        m_map.changeShowDebug();
    }
    if (keyCode == sf::Keyboard::R) {
        m_map = TileMap("SandBox2.json");
    }
}
