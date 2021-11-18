#include "ProgressBar.h"
#include <iostream>

ProgressBar::ProgressBar():
	m_minValue(0),
	m_maxValue(10),
	m_front(sf::Sprite()),
	m_back(nullptr),
	m_value(0)
{
}

ProgressBar::ProgressBar(float minValue, float maxValue, sf::Sprite front, sf::Sprite* back) :
	m_minValue(minValue),
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

	switch (m_type)
	{
	case ProgressBar::Type::Single:
		setValueSingle(value);
		break;
	case ProgressBar::Type::Multiple:
		setValueMultiple(value);
		break;
	case ProgressBar::Type::Circle:
		setValueCircle(value);
		break;
	default:
		break;
	}
}

void ProgressBar::setNumberOfSprite(size_t nbr)
{
	m_type = Type::Multiple;
	m_numberOfSprite = nbr;
	m_lstSprite.clear();
	for (size_t i = 0; i < m_numberOfSprite; i++)
	{
		m_lstSprite.push_back(m_front);
		m_lstSprite[i].setPosition(sf::Vector2f(i * 8.f, 0.f));
	}
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	switch (m_type)
	{
	case ProgressBar::Type::Single:
		if (m_back != nullptr) {
			target.draw(*m_back, states);
		}
		target.draw(m_front, states);
		break;
	case ProgressBar::Type::Multiple:
		for (size_t i = 0; i < m_numberOfSprite; i++)
		{
			if (m_back != nullptr) {
				m_back->setPosition(m_lstSprite[i].getPosition());
				target.draw(*m_back, states);
			}
			target.draw(m_lstSprite[i], states);
		}
		break;
	case ProgressBar::Type::Circle:

		break;
	default:
		break;
	}
}

void ProgressBar::setValueSingle(float value)
{
	float m_pourcentage = m_value / m_maxValue;
	m_front.setTextureRect(sf::IntRect(0, 0, m_front.getTexture()->getSize().x * m_pourcentage, m_front.getTexture()->getSize().y));
}

void ProgressBar::setValueMultiple(float value)
{
	float m_pourcentage = m_value * (m_numberOfSprite / (m_maxValue - m_minValue));
	for (size_t i = 0; i < m_numberOfSprite; i++)
	{
		float m_rectPourcentage = 0.f;
		if (m_pourcentage >= 1) {
			m_rectPourcentage = 1.f;
		}
		else {
			m_rectPourcentage = m_pourcentage;
		}

		m_lstSprite[i].setTextureRect(sf::IntRect(0, 0, m_front.getTexture()->getSize().x * m_rectPourcentage, m_front.getTexture()->getSize().y));

		m_pourcentage--;
		if (m_pourcentage < 0) {
			m_pourcentage = 0;
		}
	}
}

void ProgressBar::setValueCircle(float value)
{
}