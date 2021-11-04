#include <SFML/Graphics.hpp>
#include <iostream>

#include "ParticleSystem.h"
#include "Point.h"

#include "Player.h"
#include "TileMap.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::Clock clock; 
    window.setKeyRepeatEnabled(false);

    Player player;
    sf::Texture pTexture;
    pTexture.loadFromFile("./zizou.png");
    player.setTexture(pTexture);
    player.setScale(sf::Vector2f(0.25, 0.25));

    TileMap tileMap("SandBox2.json");
    sf::View view(tileMap.getStartingPosition().toVector2(), sf::Vector2f(200, 150));

    sf::Vector2f movement = view.getCenter();

    std::vector<sf::RectangleShape> listOfElement(10);
    for (sf::RectangleShape rectangle : listOfElement) {
        rectangle.setSize(sf::Vector2f(50, 50));
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(rand()%800, rand()%600);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) {
                    tileMap.changeShowDebug();
                }
            }
        }
        sf::Time deltaTime = clock.restart();

        player.update(deltaTime, listOfElement);
        tileMap.update(deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && movement.y > 75) {
            movement.y -= deltaTime.asSeconds() * 50;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movement.x += deltaTime.asSeconds() * 50;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            movement.y += deltaTime.asSeconds() * 50;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && movement.x > 100) {
            movement.x -= deltaTime.asSeconds() * 50;
        }
        view.setCenter(movement);

        window.clear();
        window.setView(view);
        window.draw(player);
        for (sf::RectangleShape rectangle : listOfElement) {
            window.draw(rectangle);
        }
        tileMap.draw(window);
        window.display();
    }

    return 0;
}