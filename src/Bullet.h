#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Bullet
{
public:
	Bullet();
	Bullet(float l_radius, sf::Vector2f l_position, sf::Color l_color, sf::Vector2f l_velocity);
	~Bullet();

	void Update();

	void SetOutOfLayer(bool l_layer);
	bool GetOutOfLayer()const;

	void SetCollision(bool l_collision);
	bool GetCollision()const;
	
	sf::CircleShape* GetShape();
	sf::Vector2f GetVelocity()const;

private:
	sf::CircleShape m_bullet;

	sf::Vector2f m_velocity;

	bool m_outOfLayer;

	bool m_isCollision;
};

