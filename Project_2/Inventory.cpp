#include "Inventory.h"
#include<iostream>
#include<functional>

Inventory::Inventory(size_t size, const sf::Texture* texture, const sf::Texture* itemSelectedTexture) :
	m_size(size),
	m_background(*texture),
	m_spriteItemSelected(*itemSelectedTexture),
	m_sizeRow(3)
{
	m_background.setTextureRect(sf::IntRect(0, 0, 64, 64));
	m_spriteItemSelected.setTextureRect(sf::IntRect(0, 0, 12, 12));
	m_background.setPosition(0, 86);

}

void Inventory::draw(sf::RenderWindow& window, bool debugMode)
{
	window.draw(m_background);

	for (int i = 0; i < m_lstItem.size(); i++)
	{
		sf::Vector2f offset = m_background.getPosition() + sf::Vector2f(15, 20);
		if (i == m_selectedItem) {
			m_spriteItemSelected.setPosition(sf::Vector2f(static_cast<float>((i % m_sizeRow) * 13 - 2), static_cast<float>((i / m_sizeRow) * 13 - 2)) + offset);
			window.draw(m_spriteItemSelected);
		}
		if (m_lstItem[i] != nullptr) {
			if (m_lstItem[i]->getType() != Item::Type::None) {
				m_lstItem[i]->setPosition(sf::Vector2f(static_cast<float>((i % m_sizeRow) * 13), static_cast<float>((i / m_sizeRow) * 13)) + offset);
				m_lstItem[i]->drawIcon(window, debugMode);
			}
		}
	}
}

bool Inventory::addItem(Item* item)
{
	for (size_t i = 0; i < m_lstItem.size(); ++i) {
		if (m_lstItem[i] == nullptr) {
			m_lstItem[i] = item;
			return true;
		}
		else if (m_lstItem[i]->getType() == Item::Type::None) {
			m_lstItem[i] = item;
			return true;
		}
	}
	return false;
}

void Inventory::keypressed(sf::Keyboard::Key keyCode)
{
	// Move Selection
	if (keyCode == sf::Keyboard::Z || keyCode == sf::Keyboard::W) {
		m_selectedItem -= m_sizeRow;
		if (m_selectedItem < 0) {
			m_selectedItem += static_cast<int>(m_size-1);
		}
	}
	if (keyCode == sf::Keyboard::D) {
		m_selectedItem += 1;
		if (m_selectedItem % m_sizeRow == 0) {
			m_selectedItem -= m_sizeRow;
		}
	}
	if (keyCode == sf::Keyboard::S) {
		m_selectedItem += m_sizeRow;
		if (m_selectedItem >= m_size -1) {
			m_selectedItem -= static_cast<int>(m_size-1);
		}
	}
	if (keyCode == sf::Keyboard::Q || keyCode == sf::Keyboard::A) {
		m_selectedItem -= 1;
		if (m_selectedItem % m_sizeRow == m_sizeRow -1 || m_selectedItem < 0) {
			m_selectedItem += m_sizeRow;
		}
	}

	// Use Item
	if (keyCode == sf::Keyboard::Space) {
		if (m_lstItem[m_selectedItem] != nullptr) {
			if (m_lstItem[m_selectedItem]->getType() != Item::Type::None) {
				m_lstItem[m_selectedItem]->activate();
				m_lstItem[m_selectedItem] = nullptr;
			}
		}
	}
}
