#include "Enemy.h"
#include "Utils.h"

Enemy::Enemy(sf::IntRect& zone, const sf::Texture* texture, const sf::Texture* lifebarTexture) :
	Entity("Orc", 5, texture)
{
	m_size = sf::Vector2f(8, 8);
	m_speed = 200.f;

	m_zone = zone;
	m_sprite.setOrigin(sf::Vector2f(12, 12));
	m_sprite.setPosition(sf::Vector2f(rand() % m_zone.width + m_zone.left, rand() % m_zone.height + m_zone.top));
	m_speed = 15.f;

	m_lifeBar = ProgressBar(0.f, 5.f, sf::Sprite(*lifebarTexture));
	m_lifeBar.setValue(m_life);

	setAnimations();
}

void Enemy::setAnimations() {
	// Idle
	m_animationController.addAnimation("Idle_UL", 224, 16, 0.3f);
	m_animationController.addAnimation("Idle_UR", 208, 16, 0.3f);
	m_animationController.addAnimation("Idle_DR", 176, 16, 0.3f);
	m_animationController.addAnimation("Idle_DL", 192, 16, 0.3f);
	// Walk
	m_animationController.addAnimation("Walk_UL", 368, 4, 0.3f);
	m_animationController.addAnimation("Walk_UR", 352, 4, 0.3f);
	m_animationController.addAnimation("Walk_DR", 320, 4, 0.3f);
	m_animationController.addAnimation("Walk_DL", 336, 4, 0.3f);
	// Die
	int nbrFrameDie = 12;
	float timeFrameDie = 0.15f;
	m_animationController.addAnimation("Die", 304, nbrFrameDie, timeFrameDie);
	m_timeDie = nbrFrameDie * timeFrameDie;
	// Hit
	int nbrFrameTakeHit = 4;
	float timeFrameTakeHit = 0.15f;
	m_animationController.addAnimation("Hit_UL", 112, nbrFrameTakeHit, timeFrameTakeHit);
	m_animationController.addAnimation("Hit_UR", 112, nbrFrameTakeHit, timeFrameTakeHit);
	m_animationController.addAnimation("Hit_DR", 112, nbrFrameTakeHit, timeFrameTakeHit);
	m_animationController.addAnimation("Hit_DL", 112, nbrFrameTakeHit, timeFrameTakeHit);
	m_timeTakeHit = nbrFrameTakeHit * timeFrameTakeHit;

	// Set Base Animation
	m_animationController.changeCurrentAnim("Idle_DL");
}

sf::FloatRect Enemy::getBoundingBox()
{
	return sf::FloatRect(getPosition().x, getPosition().y, m_size.x, m_size.y);
}

void Enemy::reloadDirection()
{
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

void Enemy::update(sf::Time& deltaTime, const sf::Vector2f& playerPos)
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
	case Enemy::State::TAKEHIT:
		TakeHit(deltaTime);
		break;
	case Enemy::State::CHANGEDIR:
		ChangeDir(deltaTime, playerPos);
		break;
	case Enemy::State::DIE:
		Die(deltaTime);
		break;
	default:
		break;
	}

	if (m_currentState != State::DIE &&
		m_currentState != State::TAKEHIT) {
		triggerFollow(playerPos);
		// Animation
		updateAnimation();
	}

	m_elapsedTimeSinceAttacked += deltaTime.asSeconds();

	Entity::update(deltaTime);
}

void Enemy::draw(sf::RenderWindow& window, bool debugMode)
{
	Entity::draw(window, debugMode);
	window.draw(m_lifeBar);


	// Draw range
	if (debugMode) {
		float r2 = m_range / 2;
		sf::RectangleShape rectBoundingBox;
		rectBoundingBox.setPosition(sf::Vector2f(getCenter().x - r2, getCenter().y - r2));
		rectBoundingBox.setSize(sf::Vector2f(m_range, m_range));
		rectBoundingBox.setFillColor(sf::Color(0, 255, 0, 50));
		window.draw(rectBoundingBox);
	}
}

void Enemy::Walk(sf::Time& deltaTime, const sf::Vector2f& playerPos)
{
	int changeDir = rand() % 100;

	sf::Vector2f position = m_sprite.getPosition();
	if (position.x < m_zone.left ||
		position.x > m_zone.left + m_zone.width ||
		position.y < m_zone.top ||
		position.y > m_zone.top + m_zone.height ||
		changeDir < 1) {
		m_currentState = State::CHANGEDIR;
	}
}

void Enemy::Follow(sf::Time& deltaTime, const sf::Vector2f& playerPos)
{
	double angle = Utils::angle(m_sprite.getPosition(), playerPos);
	m_velocity.x = m_speed * cos(angle);
	m_velocity.y = m_speed * sin(angle);
	reloadDirection();

	double distance = Utils::dist(m_sprite.getPosition(), playerPos);
	if (distance > m_range) {
		m_currentState = State::CHANGEDIR;
	}
}

void Enemy::TakeHit(sf::Time& deltaTime)
{
	m_chronoTakeHit += deltaTime.asSeconds();

	if (m_chronoTakeHit >= m_timeTakeHit) {
		m_chronoTakeHit = 0;
		m_currentState = State::CHANGEDIR;
	}
}

void Enemy::ChangeDir(sf::Time& deltaTime, const sf::Vector2f& playerPos)
{
	m_velocity.x = 0;
	m_velocity.y = 0;
	m_chronoChangeDir += deltaTime.asSeconds();

	if (m_chronoChangeDir >= m_timeIdle) {
		m_chronoChangeDir = 0;
		m_timeIdle = (rand() % 20 + 5) / 10.f;

		// Calcul Angle
		double angle = Utils::angle(m_sprite.getPosition(), sf::Vector2f(rand() % m_zone.width + m_zone.left, rand() % m_zone.height + m_zone.top));
		m_velocity.x = m_speed * cos(angle);
		m_velocity.y = m_speed * sin(angle);

		m_currentState = State::WALK;
		// Guard against 0 (0,00000...)
		if (m_velocity.x == 0) {
			m_velocity.x = DBL_EPSILON;
		}
		if (m_velocity.y == 0) {
			m_velocity.y = DBL_EPSILON;
		}

		reloadDirection();
	}
}


void Enemy::Die(sf::Time& deltaTime) {
	m_animationController.changeCurrentAnim("Die");
	m_chronoDie += deltaTime.asSeconds();
	if (m_chronoDie >= m_timeDie) {
		m_toRemove = true;
	}
}


void Enemy::triggerFollow(const sf::Vector2f& playerPos) {
	if (m_currentState == State::FOLLOW) { return; }
	double distance = Utils::dist(m_sprite.getPosition(), playerPos);
	if (distance < m_range) {
		m_currentState = State::FOLLOW;
	}
}

void Enemy::updateAnimation() {
	std::string base = "";
	if (m_currentState == State::TAKEHIT)
		base = "Hit";
	else if (m_velocity.x != 0 || m_velocity.y != 0)
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
}


void Enemy::takeDamage(float damage, sf::Time& deltaTime, float cooldown) { // Preferably called (to not get one shot by player)
	
	if (m_elapsedTimeSinceAttacked > cooldown) {
		takeDamage(damage); // Call normal function
		m_elapsedTimeSinceAttacked = 0;
	}
}

void Enemy::takeDamage(float damage) { // Preferably call takeDame(damge, deltaTime, cooldown) (else enemy get one shot)
	
	Entity::takeDamage(damage);

	m_lifeBar.setValue(m_life);
	if (m_life == 0) {
		m_velocity.x = 0;
		m_velocity.y = 0;
		m_currentState = State::DIE;
	}
	else {
		m_currentState = State::TAKEHIT;
		updateAnimation();
	}
}