#pragma once
#include <SFML/Graphics.hpp>
class ProgressBar : public sf::Drawable, public sf::Transformable
{
	sf::Sprite* m_back; // Not necessary
	sf::Sprite m_front;

	float m_value;
	float m_maxValue;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	ProgressBar() {}
	ProgressBar(float maxValue, sf::Sprite front, sf::Sprite* back = nullptr);
	
	void setValue(float value);
	void addValue(float value) { setValue(m_value + value); }
	float getValue() { return m_value; }
};

