#include "Enemy.h"
#include "Point.h"
#include "Utils.h"

Enemy::Enemy(sf::IntRect* zone) : Sprite()
{
	m_zone = zone;
	setOrigin(sf::Vector2f(12, 12));
	setPosition(sf::Vector2f(rand() % m_zone->width + m_zone->left, rand() % m_zone->height + m_zone->top));

	m_texture.loadFromFile("./Assets/OrcAnimations.png");
	setTexture(m_texture);
	setTextureRect(sf::IntRect(0, 352, 32, 32));
}

void Enemy::update(sf::Time deltaTime)
{
	switch (m_currentState)
	{
	case Enemy::State::NONE:
		m_currentState = State::CHANGEDIR;
		break;
	case Enemy::State::WALK:
		Walk(deltaTime);
		break;
	case Enemy::State::FOLLOW:
		Follow();
		break;
	case Enemy::State::ATTACK:
		Attack();
		break;
	case Enemy::State::CHANGEDIR:
		ChangeDir();
		break;
	default:
		break;
	}

}

void Enemy::Walk(sf::Time deltaTime)
{
	sf::Vector2f movement = m_velocity;
	movement.x *= deltaTime.asSeconds();
	movement.y *= deltaTime.asSeconds();
	move(movement);

	sf::Vector2f position = getPosition();
	if (position.x < m_zone->left ||
		position.x > m_zone->left + m_zone->width ||
		position.y < m_zone->top ||
		position.y > m_zone->top + m_zone->height) {
		m_currentState = State::CHANGEDIR;
	}
}

void Enemy::Follow()
{
}

void Enemy::Attack()
{
}

void Enemy::ChangeDir()
{
	double angle = Utils::angle(getPosition(), sf::Vector2f(rand()%m_zone->width + m_zone->left, rand() % m_zone->height + m_zone->top));
	m_velocity.x = m_speed * cos(angle);
	m_velocity.y = m_speed * sin(angle);
	m_currentState = State::WALK;
}
