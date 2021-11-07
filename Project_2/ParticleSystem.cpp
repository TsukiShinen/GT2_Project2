#include "ParticleSystem.h"
#include <iostream>

void ParticleSystem::resetParticle(size_t index)
{
	// give random velocity and lifetime
	float angle = 0;
	float speed = m_power;
	if (m_direction != nullptr)
		angle = ((std::rand() % (m_dispersion)) - (m_dispersion / 2)) * 3.14f / 180.f + atan(m_direction->y / m_direction->x);
	else
		angle = (std::rand() % 360) * 3.14f / 180.f;
	std::cout << "angle : " << angle << "\n";
	std::cout  << "cos : " << std::cos(angle) << "\n";
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);


	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// reset the position
	m_vertices[index].position = m_emitter;
	// set color
	int indexColor = std::rand() % m_color.size();
	m_vertices[index].color = m_color[indexColor];
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = NULL;
	target.draw(m_vertices, states);
}

void ParticleSystem::update(sf::Time deltaTime)
{
	for (size_t i = 0; i < m_particles.size(); ++i)
	{
		// update particle liftime
		Particle& m_lifeBar = m_particles[i];
		m_lifeBar.lifetime -= deltaTime;

		// if the particle is dead, respawn it
		if (m_lifeBar.lifetime <= sf::Time::Zero) 
		{
			resetParticle(i);
		}

		// update the position of the particle
		m_vertices[i].position += m_lifeBar.velocity * deltaTime.asSeconds();

		// update the alpha of the particle according of it s lifetime
		float ratio = m_lifeBar.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}
