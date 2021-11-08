#include "ProgressBar.h"

ProgressBar::ProgressBar(float maxValue, sf::Sprite front, sf::Sprite* back) :
	m_maxValue(maxValue),
	m_front(front), 
	m_back(back), 
	m_value(0)
{
	setValue(0);
	
}

void ProgressBar::setValue(float value)
{
	m_value = value;

	float m_pourcentage = m_value / m_maxValue;
	m_front.setTextureRect(sf::IntRect(0, 0, m_front.getTexture()->getSize().x * m_pourcentage, m_front.getTexture()->getSize().y));
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (m_back != nullptr) {
		target.draw(*m_back, states);
	}
	target.draw(m_front, states);
}
