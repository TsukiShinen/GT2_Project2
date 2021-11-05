#include "Enemy.h"
#include "Point.h"
#include "Utils.h"

Enemy::Enemy() : Sprite()
{
	m_texture.loadFromFile("./Assets/OrcAnimations.png");
	setTexture(m_texture);
	setTextureRect(sf::IntRect(0, 352, 32, 32));
}

void Enemy::update(sf::Time deltaTime)
{
	sf::Vector2f movement = m_velocity;
	movement.x *= deltaTime.asSeconds();
	movement.y *= deltaTime.asSeconds();
	move(movement);
}

void Enemy::randomAngle()
{
	m_angle = Utils::angle(getPosition(), sf::Vector2f(175, 150));
	m_velocity.x = m_speed * cos(m_angle);
	m_velocity.y = m_speed * sin(m_angle);
}
