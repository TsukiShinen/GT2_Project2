#include "Sword.h"
Sword::Sword(const sf::Texture* texture) :
	Entity("Sword", 100, texture)
{
	setAnimation();
	m_size = sf::Vector2f(8, 8);
	m_sprite.setOrigin(m_rotationPoint);

}

void Sword::setAnimation() {
	m_animationController.addAnimation("Normal", 384, 4, 0.23f);
	m_animationController.addAnimation("Start", 384, 15, 0.23f);
	m_animationController.addAnimation("Fire", 388, 11, 0.23f);
	m_animationController.changeCurrentAnim("Fire");
}

void Sword::attack(int angle) {
	m_ratio = 180 / m_attackSpeed;
	m_startAngle = (angle - 180 + 360) % 360;
	if (angle <= 180) {
		m_ratio *= (-1);
	}
	m_sprite.setRotation(m_startAngle);
}

void Sword::update(sf::Time deltaTime, sf::Vector2f position, bool isAttacking, sf::Vector2f direction) {
	int rotation = m_sprite.getRotation();
	if(m_elapsedTime != 0) {
		if (m_elapsedTime > m_attackSpeed) {
			m_sprite.setRotation(0);
			m_elapsedTime = 0;
		}
		else {
			int tempAngle = (rotation + int(m_ratio) + 360)%360;
			m_sprite.setRotation(tempAngle);

		}
	}

	setPosition(position);
}