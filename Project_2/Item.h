#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include<functional>
class Item
{
public:
	enum class Type { None, Potion };

	Item(std::string name, sf::Sprite* icon, Type type, std::function<void(int)>& function);

	void drawIcon(sf::RenderWindow& window, bool debugMode);
	void setPosition(const sf::Vector2f& position);
	Type getType();
	std::function<void(int)> use;
private:
	std::string m_name = "";
	sf::Sprite m_icon;

	Type m_type = Type::None;

};

