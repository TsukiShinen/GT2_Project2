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
		// m_ratio *= (-1);
		m_startAngle = fmod((angle - 90 + 360), 360);
	}
	else {
		m_ratio *= (-1);
		m_startAngle = fmod((angle + 90  + 360), 360);
	}
	m_hitting = true;
	m_startAngle += m_offsetAngle;
	m_sprite.setRotation(m_startAngle);

}

void Sword::update(sf::Time deltaTime, sf::Vector2f position, bool isAttacking, float angle) {
	int actualRotation = m_sprite.getRotation() + m_offsetAngle;
	
	
	if (m_hitting) {

			float tempAngle = fmod(ceil(m_startAngle + (180 * (m_elapsedTime/m_attackSpeed) * m_ratio) + 360), 360);
			m_elapsedTime += deltaTime.asSeconds();
			m_sprite.setRotation(tempAngle);
			if (m_elapsedTime > m_attackSpeed) {

				m_hitting = false;
				m_elapsedTime = 0;
			}

	}
	/*else {
		
		m_sprite.setRotation(actualRotation + ((angle- actualRotation) * m_elapsedTime/m_attackSpeed));
		if (m_elapsedTime > m_angleRecovery) {
			m_elapsedTime = 0;
		}
	}
	*/
	setPosition(position);
	Entity::update(deltaTime);
}