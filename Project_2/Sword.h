#pragma once
#include "Entity.h"
#include <math.h>
class Sword : public Entity
{
private:
	sf::Vector2f m_rotationPoint {15, 16};
	int m_range = 12;
	float m_damage = 2;
	
	float m_attackSpeed = 0.15f;
	float m_elapsedTimeSinceAttacked = 0;

	float m_angleRecovery = 0.21f;

	float m_offsetAngle = 90.f;
	float m_attackAngle = 90.f;

	float m_ratio = 180/m_attackSpeed;
	double m_startAngle = 1;

	bool m_hitting = false;

public:
	Sword(const sf::Texture* texture);
	void setAnimation();
	void attack(double angle);
	float& getDamage() { return m_damage; };
	int& getRange() { return m_range; };
	float& getAttackAngle() { return m_attackAngle; }
	float& getAttackSpeed() { return m_attackSpeed; }
	void update(sf::Time deltaTime, float angle);
	bool isHitting() { return m_hitting; }
};
