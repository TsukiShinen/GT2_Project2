#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ressource
{
	sf::Texture* playerTexture = new sf::Texture();
	sf::Texture* orcTexture = new sf::Texture();

	sf::Texture* lifeBar = new sf::Texture();
public:
	void loadTexture() {
		if (!playerTexture->loadFromFile("./Assets/PlayerAnimations.png")) {
			std::cout << "Can't load Player Texture !" << std::endl;
			return; 
		}
		if (!orcTexture->loadFromFile("./Assets/OrcAnimations.png")) {
			std::cout << "Can't load Orc Texture !" << std::endl;
			return;
		}
		if (!lifeBar->loadFromFile("./Assets/lifeBar.png")) {
			std::cout << "Can't load lifebar Texture !" << std::endl;
			return;
		}

		std::cout << "Succefully load Textures." << std::endl;
	}

	const sf::Texture* getPlayerTexture() { return playerTexture; }
	const sf::Texture* getOrcTexture() { return orcTexture; }
	const sf::Texture* getlifeBarTexture() { return lifeBar; }
};

