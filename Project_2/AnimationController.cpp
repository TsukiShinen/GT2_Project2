#include "AnimationController.h"

void AnimationController::changeCurrentAnim(std::string name) {
	if (m_animationName == name) { return; }
	m_animations[m_animationName].stop();
	m_animationName = name;
	m_animations[m_animationName].play();
}

void AnimationController::update(sf::Time deltaTime) {
	m_animations[m_animationName].update(deltaTime);
}

std::vector<sf::IntRect> AnimationController::getAllRect(std::vector<size_t> lstId)
{
	std::vector<sf::IntRect> lstRect;

	for (size_t& id : lstId) {
		sf::Vector2f pos(static_cast<float>(id % m_columns), static_cast<float>(id) / m_columns);

		lstRect.push_back(sf::IntRect(static_cast<int>(pos.x) * static_cast<int>(m_tileSizeX),
			static_cast<int>(pos.y) * static_cast<int>(m_tileSizeY),
			static_cast<int>(m_tileSizeX),
			static_cast<int>(m_tileSizeY)));
	}

	return lstRect;
}

std::vector<sf::IntRect> AnimationController::getAllRect(size_t idBegin, size_t nbr)
{
	std::vector<size_t> range;
	for (size_t i = idBegin; i < idBegin + nbr; ++i)
	{
		range.push_back(i);
	}

	return getAllRect(range);
}
