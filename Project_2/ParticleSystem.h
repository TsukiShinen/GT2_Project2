#pragma once
#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, sf::Transform
{
	struct Particle 
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	std::vector<sf::Color> m_color;
	float m_power;
	
	sf::Vector2f* m_direction;
	int m_dispersion;

	void resetParticle(size_t index);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	ParticleSystem(unsigned int count, sf::Vector2f emitter, float power = 10.f, sf::Vector2f* direction = nullptr, int dispersion = 45, 
		std::vector<sf::Color> color = std::vector<sf::Color>()) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_lifetime(sf::seconds(3.f)),
		m_emitter(emitter),
		m_color(color),
		m_direction(direction),
		m_dispersion(dispersion),
		m_power(power)
	{
		if (m_color.empty()) {
			m_color.push_back(sf::Color::White);
		}
	}

	~ParticleSystem() 
	{
		delete m_direction;
	}

	void setEmitter(sf::Vector2f position) { m_emitter = position; }
	void update(sf::Time deltaTime);
};

