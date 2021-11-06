#include "Enemy.h"
#include "Point.h"
#include "Utils.h"

Enemy::Enemy(sf::IntRect* zone)
{
	m_zone = zone;
	m_sprite.setOrigin(sf::Vector2f(12, 12));
	m_sprite.setPosition(sf::Vector2f(rand() % m_zone->width + m_zone->left, rand() % m_zone->height + m_zone->top));

	m_texture.loadFromFile("./Assets/OrcAnimations.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 352, 32, 32));


	m_textureLifeBar.loadFromFile("./Assets/lifeBar.png");
	m_lifeBar = ProgressBar(5.f, sf::Sprite(m_textureLifeBar));
	m_lifeBar.setValue(5.f);
}

void Enemy::update(sf::Time& deltaTime)
{
	// Life bar
	sf::Vector2f position = m_sprite.getPosition();
	m_lifeBar.setPosition(sf::Vector2f(position.x, position.y - 4));

	switch (m_currentState)
	{
	case Enemy::State::NONE:
		m_currentState = State::CHANGEDIR;
		break;
	case Enemy::State::WALK:
		Walk(deltaTime);
		break;
	case Enemy::State::FOLLOW:
		Follow(deltaTime);
		break;
	case Enemy::State::ATTACK:
		Attack(deltaTime);
		break;
	case Enemy::State::CHANGEDIR:
		ChangeDir(deltaTime);
		break;
	default:
		break;
	}

}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_lifeBar);
}

void Enemy::Walk(sf::Time& deltaTime)
{
	sf::Vector2f movement = m_velocity;
	movement.x *= deltaTime.asSeconds();
	movement.y *= deltaTime.asSeconds();
	m_sprite.move(movement);

	int changeDir = rand() % 100;

	sf::Vector2f position = m_sprite.getPosition();
	if (position.x < m_zone->left ||
		position.x > m_zone->left + m_zone->width ||
		position.y < m_zone->top ||
		position.y > m_zone->top + m_zone->height ||
		changeDir < 1) {
		m_currentState = State::CHANGEDIR;
	}
}

void Enemy::Follow(sf::Time& deltaTime)
{
}

void Enemy::Attack(sf::Time& deltaTime)
{
}

void Enemy::ChangeDir(sf::Time& deltaTime)
{
	m_chronoChangeDir += deltaTime.asSeconds();

	if (m_chronoChangeDir >= m_timeIdle) {
		m_chronoChangeDir = 0;
		double angle = Utils::angle(m_sprite.getPosition(), sf::Vector2f(rand() % m_zone->width + m_zone->left, rand() % m_zone->height + m_zone->top));
		m_velocity.x = m_speed * cos(angle);
		m_velocity.y = m_speed * sin(angle);
		m_currentState = State::WALK;
	}
}
