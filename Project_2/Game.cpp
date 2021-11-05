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

    m_orc = new Enemy();
    m_orc->setPosition(m_map.getStartingPosition().toVector2() - sf::Vector2f(32, 0));
    m_orc->randomAngle();

    gameView.setCenter(m_player.getPosition());
    gameView.setSize((m_screenSize/4).toVector2());
}

void Game::update(sf::Time& deltaTime)
{
    m_player.update(deltaTime, listOfElement);
    m_orc->update(deltaTime);
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
    window.draw(*m_orc);
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
