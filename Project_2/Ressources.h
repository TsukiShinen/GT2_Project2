#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ressource
{
	sf::Texture* playerTexture = new sf::Texture();
	sf::Texture* orcTexture = new sf::Texture();

	sf::Texture* lifeBar = new sf::Texture();
	sf::Texture* inventory = new sf::Texture();
	sf::Texture* items = new sf::Texture();
	sf::Texture* itemSelected = new sf::Texture();


	sf::Font* mainFont = new sf::Font();
public:
	void load() {
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
		if (!inventory->loadFromFile("./Assets/Inventaire.png")) {
			std::cout << "Can't load inventory Texture !" << std::endl;
			return;
		}
		if (!items->loadFromFile("./Assets/Items.png")) {
			std::cout << "Can't load Items Texture !" << std::endl;
			return;
		}
		if (!itemSelected->loadFromFile("./Assets/itemSelected.png")) {
			std::cout << "Can't load itemSelected Texture !" << std::endl;
			return;
		}

		std::cout << "Succefully load Textures." << std::endl;

		if (!mainFont->loadFromFile("./Assets/Fonts/Pixel_4x4.ttf")) {
			std::cout << "Can't load main font !" << std::endl;
			return;
		}
		const_cast<sf::Texture&>(mainFont->getTexture(6)).setSmooth(false);

		std::cout << "Succefully load Fonts." << std::endl;
	}

	const sf::Texture* getPlayerTexture() { return playerTexture; }
	const sf::Texture* getOrcTexture() { return orcTexture; }
	const sf::Texture* getlifeBarTexture() { return lifeBar; }
	const sf::Texture* getInventoryTexture() { return inventory; }
	const sf::Texture* getItemSelected() { return itemSelected; }
	sf::Sprite* getMeat() {
		return new sf::Sprite(*items, sf::IntRect(0, 96, 8, 8));
	}

	sf::Font* getMainFont() { return mainFont; }
};

