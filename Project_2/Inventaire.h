#pragma once
#include<vector>
#include <SFML/Graphics.hpp>

#include "Item.h"

class Inventaire
{
	size_t m_size;

	std::vector<Item*> m_lstItem{ 9 };

	sf::Sprite m_background;
	sf::Sprite m_spriteItemSelected;
	int m_selectedItem = 0;

public:
	Inventaire(size_t size, const sf::Texture* texture, const sf::Texture* itemSelectedTexture);

	void draw(sf::RenderWindow& window, bool debugMode);

	bool addItem(Item* item);
	void keypressed(sf::Keyboard::Key keyCode);
};

