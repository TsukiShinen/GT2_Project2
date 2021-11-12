#include "Item.h"

Item::Item(std::string name, sf::Sprite* icon, Type type, std::function<void(int)>& function):
	m_name(name),
	m_icon(*icon),
	m_type(type)
{
	use = function;
}

void Item::drawIcon(sf::RenderWindow& window, bool debugMode)
{
	window.draw(m_icon);
}

void Item::setPosition(const sf::Vector2f& position)
{
	m_icon.setPosition(position);
}

Item::Type Item::getType()
{
	return m_type;
}
