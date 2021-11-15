#include "Sword.h"
Sword::Sword(const sf::Texture* texture) :
	Entity("Sword", 100, texture)
{
	setAnimation();
	m_size = sf::Vector2f(8, 8);
	m_sprite.setOrigin(m_rotationPoint);

}

void Sword::setAnimation() {
	m_animationController.addAnimation("Normal", 400, 4, 0.23f);
	m_animationController.addAnimation("Start", 400, 15, 0.13f);
	m_animationController.addAnimation("Fire", 404, 11, 0.10f);
	m_animationController.changeCurrentAnim("Start");
}

void Sword::attack(float angle) {
	angle = fmod((angle + 360), 360);
	m_ratio = 1; // ceil(180/ m_attackSpeed);
	
	if (angle <= 90 || angle >= 270) {
		m_ratio *= (-1);
		m_startAngle = fmod((angle + 90 + 360), 360);
	}
	else {
		
		m_startAngle = fmod((angle - 90 + 360), 360);
	}
	m_hitting = true;
	m_sprite.setRotation(m_startAngle);
	std::cout << "Original angle : " << angle << std::endl;
	std::cout << "Start angle : " << m_startAngle << std::endl;
}

void Sword::update(sf::Time deltaTime, sf::Vector2f position, bool isAttacking) {
		if (m_hitting) {
			int actualRotation = m_sprite.getRotation();
			m_elapsedTime += deltaTime.asSeconds();
			
			float tempAngle = fmod(ceil(m_startAngle + (180 * (m_elapsedTime/m_attackSpeed) * m_ratio) + 360), 360);

			m_sprite.setRotation(tempAngle);
			if (m_elapsedTime > m_attackSpeed) {
				m_sprite.setRotation(0);

				m_hitting = false;
				m_elapsedTime = 0;
			}
		}

	setPosition(position);
	Entity::update(deltaTime);
}