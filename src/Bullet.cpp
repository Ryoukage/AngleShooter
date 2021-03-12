#include "Bullet.h"

Bullet::Bullet()
{
	
}

Bullet::Bullet(float l_radius, sf::Vector2f l_position, sf::Color l_color, sf::Vector2f l_velocity, sf::Text l_text) :m_velocity(l_velocity), m_outOfLayer(false), m_isCollision(false), m_time(1.f), m_miss(false)
{
	m_bullet.setRadius(l_radius);
	m_bullet.setPosition(l_position);
	m_bullet.setFillColor(l_color);
	
	m_text = l_text;
}

sf::CircleShape* Bullet::GetShape()
{
	return &m_bullet;
}

sf::Vector2f Bullet::GetVelocity()const
{
	return m_velocity;
}

void Bullet::SetOutOfLayer(bool l_layer)
{
	m_outOfLayer = l_layer;
}

void Bullet::SetCollision(bool l_collision)
{
	m_isCollision = l_collision;
}

bool Bullet::GetCollision()const
{
	return m_isCollision;
}

void Bullet::SetMiss(bool l_miss)
{
	m_miss = l_miss;
}

void Bullet::SetColor(sf::Color l_color)
{
	m_color = l_color;
}

void Bullet::Update(sf::Time time)
{
	if (m_miss)
	{
		m_time -= time.asSeconds();
		m_color.a = 255 * m_time;
		m_text.setFillColor(m_color);
		m_text.move(0.f, -250.f * time.asSeconds());
		if (m_time < 0.f)
		{
			m_miss = false;
		}
	}
}

sf::Text* Bullet::GetText()
{
	return &m_text;
}

bool Bullet::GetOutOfLayer()const
{
	return m_outOfLayer;
}

Bullet::~Bullet(){}
