#include "Sword.h"
Sword::Sword(const sf::Texture* texture) :
	Entity("Sword", 100, texture)
{
	m_size = sf::Vector2f(8, 8);
	m_sprite.setOrigin(m_rotationPoint);
	m_useAcceleration = false;
	setAnimation();
}

void Sword::setAnimation() {
	m_animationController.addAnimation("Normal", 400, 4, 0.23f);
	m_animationController.addAnimation("Start", 400, 15, 0.13f);
	m_animationController.addAnimation("Fire", 404, 11, 0.10f);
	m_animationController.changeCurrentAnim("Start");
}

void Sword::attack(double angle) {
	// Get angle attack
	angle = fmod((angle + 360), 360);
	m_ratio = 1;
	
	// Get the starting angle
	if (angle <= 90 || angle >= 270) {
		m_startAngle = fmod((angle - 90 + 360), 360);
	}
	else {
		m_ratio *= (-1);
		m_startAngle = fmod((angle + 90  + 360), 360);
	}

	// Play the attack
	m_hitting = true;
	m_startAngle += m_offsetAngle;
	m_sprite.setRotation(static_cast<float>(m_startAngle));
}

void Sword::update(sf::Time deltaTime, float angle) {
	float actualRotation = m_sprite.getRotation() + m_offsetAngle;
	
	
	if (m_hitting) {

			double newAngle = fmod(ceil(m_startAngle + (180 * m_ratio * m_elapsedTimeSinceAttacked / m_attackSpeed) + 360), 360);
			m_elapsedTimeSinceAttacked += deltaTime.asSeconds();
			m_sprite.setRotation(static_cast<float>(newAngle));
			if (m_elapsedTimeSinceAttacked > m_attackSpeed) {
				m_hitting = false;
				m_elapsedTimeSinceAttacked = 0;
			}

	}
	updateAniamtion(deltaTime);
}

