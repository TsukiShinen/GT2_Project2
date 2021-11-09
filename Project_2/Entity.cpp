#include "Entity.h"

void Entity::update(sf::Time& deltaTime)
{
	// Move the sprite
	m_sprite.move(m_velocity * deltaTime.asSeconds());

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

sf::Vector2f Entity::getPosition()
{
	return m_sprite.getPosition();
}
