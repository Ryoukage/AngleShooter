#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class ParticleSystem :public sf::Drawable, public sf::Transformable 
{
public:
	ParticleSystem(){}
	ParticleSystem(unsigned int count) :m_particle(count), m_vertices(sf::Points, count), m_lifetime(sf::seconds(3.f)), m_emitter(0.f, 0.f) 
	{

	}

	void setEmitter(sf::Vector2f position) 
	{
		m_emitter = position;
	}
	
	void update(sf::Time elapsed)
	{
		for (std::size_t i = 0; i < m_particle.size(); ++i)
		{
			Particle& p = m_particle[i];
			p.lifetime -= elapsed;

			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			m_vertices[i].position += p.velocity * elapsed.asSeconds();

			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const 
	{
		//Apply the tranform
		states.transform *= getTransform();

		//Particle dont use vertex
		states.texture = NULL;

		//Draw the vertex array
		target.draw(m_vertices, states);
	}

private:
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
	};

	void resetParticle(std::size_t index) 
	{
		//give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14 / 180.f;
		float speed = (std::rand() % 50) + 50.f;
		m_particle[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particle[index].lifetime = sf::milliseconds((std::rand() % 3000) + 1000);

		//reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
	}

	std::vector<Particle>m_particle;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
};