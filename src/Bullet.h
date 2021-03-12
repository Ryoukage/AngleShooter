#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Bullet
{
public:
	Bullet();
	Bullet(float l_radius, sf::Vector2f l_position, sf::Color l_color, sf::Vector2f l_velocity,sf::Text l_text);
	~Bullet();

	void Update(sf::Time time);

	void SetOutOfLayer(bool l_layer);
	bool GetOutOfLayer()const;

	void SetCollision(bool l_collision);
	bool GetCollision()const;

	void SetMiss(bool l_miss);
	void SetColor(sf::Color l_color);

	sf::Text* GetText();
	
	sf::CircleShape* GetShape();
	sf::Vector2f GetVelocity()const;

private:
	sf::CircleShape m_bullet;

	sf::Vector2f m_velocity;
	
	sf::Text m_text;

	sf::Color m_color;

	float m_time;

	bool m_outOfLayer;

	bool m_isCollision;
	bool m_miss;
};

