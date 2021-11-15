#include "Camera.h"
#include <iostream>

Camera::Camera()
{
}

void Camera::setView(sf::View view)
{
	m_view = view;
}

sf::View& Camera::getView()
{
	return m_view;
}

void Camera::Follow(const sf::Time& deltaTime, const sf::Vector2f& follow)
{
	sf::Vector2f thrust(follow.x - m_view.getCenter().x, follow.y - m_view.getCenter().y);
	m_velocity = (1 - m_friction) * m_velocity + thrust;
	if (abs(m_velocity.x) < m_friction) {
		m_velocity.x = 0;
	}
	if (abs(m_velocity.y) < m_friction) {
		m_velocity.y = 0;
	}

	m_view.setCenter(m_view.getCenter() + m_velocity * deltaTime.asSeconds());
}
