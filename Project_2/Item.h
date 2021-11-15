#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include<functional>
class Item
{
public:
	enum class Type { None, Potion };

	Item(std::string name, sf::Sprite* icon, Type type, std::function<void(int)>& function, int value = 3);

	void drawIcon(sf::RenderWindow& window, bool debugMode);
	void setPosition(const sf::Vector2f& position);
	sf::FloatRect getBoundingBox();
	Type getType();
	void activate();
private:
	std::string m_name = "";
	sf::Sprite m_icon;
	int m_value;

	Type m_type = Type::None;

	std::function<void(int)> use;
};

