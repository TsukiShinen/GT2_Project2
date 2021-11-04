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
    pTexture.loadFromFile("./Assets/PlayerAnimations.png");
    player.setTexture(pTexture);
    player.setTextureRect(sf::IntRect(12, 364, 8, 8));

    TileMap tileMap("SandBox2.json");
    sf::View view(tileMap.getStartingPosition().toVector2(), sf::Vector2f(200, 150));
    player.setPosition(tileMap.getStartingPosition().toVector2());

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

        sf::Vector2f cameraPosition = player.getPosition();
        if (cameraPosition.y < 75) {
            cameraPosition.y = 75;
        }
        if (cameraPosition.x < 100) {
            cameraPosition.x = 100;
        }
        view.setCenter(cameraPosition);

        window.clear();
        window.setView(view);
        tileMap.draw(window);
        window.draw(player);
        for (sf::RectangleShape rectangle : listOfElement) {
            window.draw(rectangle);
        }
        window.display();
    }

    return 0;
}