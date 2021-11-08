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

	// Animation
	m_animationController.addAnimation("Idle_UL", Animation(m_animationController.getAllRect(224, 16), 0.3f));
	m_animationController.addAnimation("Idle_UR", Animation(m_animationController.getAllRect(208, 16), 0.3f));
	m_animationController.addAnimation("Idle_DR", Animation(m_animationController.getAllRect(176, 16), 0.3f));
	m_animationController.addAnimation("Idle_DL", Animation(m_animationController.getAllRect(192, 16), 0.3f));
	m_animationController.addAnimation("Walk_UL", Animation(m_animationController.getAllRect(368, 4), 0.3f));
	m_animationController.addAnimation("Walk_UR", Animation(m_animationController.getAllRect(352, 4), 0.3f));
	m_animationController.addAnimation("Walk_DR", Animation(m_animationController.getAllRect(320, 4), 0.3f));
	m_animationController.addAnimation("Walk_DL", Animation(m_animationController.getAllRect(336, 4), 0.3f));
	m_animationController.changeCurrentAnim("Idle_DL");
}

void Enemy::update(sf::Time& deltaTime, sf::Vector2f playerPos)
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
		Walk(deltaTime, playerPos);
		break;
	case Enemy::State::FOLLOW:
		Follow(deltaTime, playerPos);
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

	// Animation
	std::string base = "";
	if (m_velocity.x != 0 || m_velocity.y != 0)
		base = "Walk";
	else
		base = "Idle";

	std::string dir = "";
	if (m_direction.up)
		dir += "U";
	else if (m_direction.down)
		dir += "D";
	if (m_direction.right)
		dir += "R";
	else if (m_direction.left)
		dir += "L";

	std::string name = base + "_" + dir;
	m_animationController.changeCurrentAnim(name);
	m_animationController.update(deltaTime);
	m_sprite.setTextureRect(m_animationController.getCurrentRect());
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_lifeBar);
}

void Enemy::Walk(sf::Time& deltaTime, sf::Vector2f playerPos)
{
	// Move
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

	// Look player
	float distance = Utils::dist(m_sprite.getPosition(), playerPos);
	if (distance < m_range) {
		m_currentState = State::FOLLOW;
	}
}

void Enemy::Follow(sf::Time& deltaTime, sf::Vector2f playerPos)
{
	double angle = Utils::angle(m_sprite.getPosition(), playerPos);
	m_velocity.x = m_speed * cos(angle);
	m_velocity.y = m_speed * sin(angle);

	// Move
	sf::Vector2f movement = m_velocity;
	movement.x *= deltaTime.asSeconds();
	movement.y *= deltaTime.asSeconds();
	m_sprite.move(movement);

	float distance = Utils::dist(m_sprite.getPosition(), playerPos);
	if (distance > m_range) {
		m_currentState = State::CHANGEDIR;
	}
}

void Enemy::Attack(sf::Time& deltaTime)
{
}

void Enemy::ChangeDir(sf::Time& deltaTime)
{
	m_velocity.x = 0;
	m_velocity.y = 0;
	m_chronoChangeDir += deltaTime.asSeconds();

	if (m_chronoChangeDir >= m_timeIdle) {
		m_chronoChangeDir = 0;
		m_timeIdle = (rand() % 20 + 5	) / 10.f;
		double angle = Utils::angle(m_sprite.getPosition(), sf::Vector2f(rand() % m_zone->width + m_zone->left, rand() % m_zone->height + m_zone->top));
		m_velocity.x = m_speed * cos(angle);
		m_velocity.y = m_speed * sin(angle);
		m_currentState = State::WALK;

		// Get the direction
		m_direction.reset();
		if (m_velocity.y < 0)
			m_direction.up = true;
		if (m_velocity.x > 0)
			m_direction.right = true;
		if (m_velocity.y > 0)
			m_direction.down = true;
		if (m_velocity.x < 0)
			m_direction.left = true;
	}
}
