#include "AnimationController.h"
#include "Point.h"

void AnimationController::changeCurrentAnim(std::string name) {
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
		Point pos(id % m_columns, id / m_columns);

		lstRect.push_back(sf::IntRect(pos.x * m_tileSizeX, pos.y * m_tileSizeY, m_tileSizeX, m_tileSizeY));
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
