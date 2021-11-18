#pragma once
#include <SFML/Graphics.hpp>
class ProgressBar : public sf::Drawable, public sf::Transformable
{
public:
	enum class Type { Single, Multiple, Circle };

	ProgressBar();
	ProgressBar(float minValue, float maxValue, sf::Sprite front, sf::Sprite* back = nullptr);
	
	void setValue(float value);
	void addValue(float value) { setValue(m_value + value); }
	float getValue() { return m_value; }

	void setNumberOfSprite(size_t nbr);
private:
	sf::Sprite* m_back; // Not necessary
	sf::Sprite m_front;
	std::vector<sf::Sprite> m_lstSprite;

	float m_value;
	float m_maxValue;
	float m_minValue;

	Type m_type = Type::Single;

	size_t m_numberOfSprite{ 0 };

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setValueSingle(float value);
	void setValueMultiple(float value);
	void setValueCircle(float value);
};

