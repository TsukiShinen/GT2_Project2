#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ParticleSystem.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::Clock clock;

    Player player;
    sf::Texture pTexture;
    pTexture.loadFromFile("./zizou.png");
    player.setTexture(pTexture);
    player.setScale(sf::Vector2f(0.25, 0.25));

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
        }
        sf::Time deltaTime = clock.restart();

        player.update(deltaTime, listOfElement);
        
        window.clear();
        window.draw(player);
       for (sf::RectangleShape rectangle : listOfElement) {
            window.draw(rectangle);
       }
        window.display();
    }

    return 0;
}