#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(float l_radius, sf::Vector2f l_position, sf::Color l_color, sf::Vector2f l_velocity) :m_velocity(l_velocity), m_outOfLayer(false), m_isCollision(false)
{
	m_bullet.setRadius(l_radius);
	m_bullet.setPosition(l_position);
	m_bullet.setFillColor(l_color);
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

void Bullet::Update()
{
	
}

bool Bullet::GetOutOfLayer()const
{
	return m_outOfLayer;
}

Bullet::~Bullet(){}