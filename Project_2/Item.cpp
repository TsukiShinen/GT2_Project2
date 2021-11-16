#include "Item.h"

Item::Item(std::string name, sf::Sprite* icon, Type type, std::function<void(int)>& function, int value):
	m_name(name),
	m_icon(*icon),
	m_type(type),
	m_value(value)
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

sf::FloatRect Item::getBoundingBox()
{
	return m_icon.getGlobalBounds();
}

Item::Type Item::getType()
{
	return m_type;
}

void Item::activate()
{
	use(m_value);
}
