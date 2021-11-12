#include "Entity.h"
#include <iostream>
#include "Utils.h"

Entity::Entity(std::string name, size_t life, const sf::Texture* texture) :
	m_name(name),
	m_life(life),
	m_sprite(*texture)
{

}

void Entity::update(sf::Time& deltaTime)
{
	// Move the sprite
	m_sprite.move(Utils::normalize(m_velocity) * m_speed * deltaTime.asSeconds());

	// Animate
	m_animationController.update(deltaTime);
	m_sprite.setTextureRect(m_animationController.getCurrentRect());
}

void Entity::draw(sf::RenderWindow& window, bool debugMode)
{
	// Draw entity
	window.draw(m_sprite);

	// Draw boundingBox
	if (debugMode) {
		sf::FloatRect boundingBox = getBoundingBox();
		sf::RectangleShape rectBoundingBox;
		rectBoundingBox.setPosition(sf::Vector2f(boundingBox.left, boundingBox.top));
		rectBoundingBox.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));
		rectBoundingBox.setFillColor(sf::Color(255, 0, 0, 50));
		window.draw(rectBoundingBox);
	}
}

const sf::Vector2f& Entity::getPosition()
{
	return m_sprite.getPosition();
}

const sf::Vector2f& Entity::getCenter()
{
	return (getPosition() + sf::Vector2f(m_size.x / 2, m_size.y / 2));
}

int Entity::getMapLevel()
{
	return m_mapLevel;
}

void Entity::setMapLevel(int level)
{
	m_mapLevel = level;
}

bool Entity::collides(const sf::FloatRect& rect)
{
	return getBoundingBox().intersects(rect);
}

void Entity::takeDamage(float damage)
{
	m_life -= damage;
	if (m_life <= 0) {
		m_life = 0;
	}
}

bool Entity::toRemove()
{
	return m_toRemove;
}

bool Entity::isAlive()
{
	return m_life > 0;
}

void Entity::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

const sf::Vector2f& Entity::getSize()
{
	return m_size;
}

