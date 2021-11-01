#include <SFML/Graphics.hpp>

#include "ParticleSystem.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::Clock clock;

    // test for the particle system
    std::vector<sf::Color> particlesColor{ sf::Color(226, 40, 34), sf::Color(226, 56, 34), sf::Color(226, 72, 34), sf::Color(226, 88, 34), sf::Color(226, 104, 34), sf::Color(226, 120, 34), sf::Color(226, 136, 34), };
    ParticleSystem particles(50, sf::Vector2f(100.f, 100.f), 10.f, new sf::Vector2f(0.f, -1.f), 45, particlesColor);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time deltaTime = clock.restart();

        // test for the particle system
        particles.update(deltaTime);

        window.clear();
        // test for the particle system
        window.draw(particles);
        window.display();
    }

    return 0;
}