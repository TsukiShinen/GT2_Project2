#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera();
	void setView(sf::View);
	sf::View& getView();
	void Follow(const sf::Time& deltaTime, const sf::Vector2f& follow);

private:
	sf::View m_view;

	sf::Vector2f m_velocity{ 0.f, 0.f };
	float m_friction{ 0.5f };
};

