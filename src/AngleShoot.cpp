#include "AngleShoot.h"


AngleShoot::AngleShoot() :m_hit(false), m_coolDownTime(0.f)
{
	if (!m_shootSoundBuffer.loadFromFile("debris_2.wav"))
	{
		
	}

	m_shootSound.setBuffer(m_shootSoundBuffer);

	m_triangle.setPointCount(3);
	m_triangle.setRadius(50.f);
	m_triangle.setPosition(sf::Vector2f(600.f, 360.f));
	m_triangle.setFillColor(sf::Color::Green);
	m_triangle.setOrigin(sf::Vector2f({ 50.f,50.f }));
}

AngleShoot::~AngleShoot(){}

void AngleShoot::SetRotation(float l_rotation)
{
	m_triangle.setRotation(l_rotation);
}

void AngleShoot::Move(sf::Vector2f l_move)
{
	m_triangle.move(l_move);
}

void AngleShoot::Shoot(double l,double r)
{
	//DO OFFSET WINDOW	
	if (m_coolDownTime > m_shootTime) 
	{
		m_shootSound.play();
		m_bulletAmmo.push_back(Bullet(10.f, sf::Vector2f(m_triangle.getPosition().x - 10.f, m_triangle.getPosition().y - 10.f), sf::Color::Cyan, sf::Vector2f(l, r)));
		m_coolDownTime = 0.f;
	}
}

void AngleShoot::SetHit(bool l_hit)
{
	m_hit = l_hit;
}

bool AngleShoot::GetHit()const
{
	return m_hit;
}

void AngleShoot::Update(sf::Time time,UI& l_ui)
{
	m_shootTime = l_ui.m_shootCooldown;
	m_coolDownTime += time.asSeconds();
	m_triangle.setFillColor(sf::Color::White);
	if (m_coolDownTime > m_shootTime)
	{
		m_triangle.setFillColor(sf::Color::Green);
	}

	for (auto itr = m_bulletAmmo.begin(); itr != m_bulletAmmo.end(); ++itr)
	{
		itr->GetShape()->move(itr->GetVelocity().x * time.asSeconds() * 120, itr->GetVelocity().y * time.asSeconds() * 120);
		if (itr->GetShape()->getPosition().x > m_triangle.getPosition().x * 2 || itr->GetShape()->getPosition().y > m_triangle.getPosition().y * 2
			|| itr->GetShape()->getPosition().x < 0 || itr->GetShape()->getPosition().y < 0)
		{
			itr->SetOutOfLayer(true);
		}
	}
	m_bulletAmmo.erase(std::remove_if(m_bulletAmmo.begin(), m_bulletAmmo.end(), [](Bullet& aloc)->bool
		{
			return aloc.GetOutOfLayer();
		}), m_bulletAmmo.end());
}

void AngleShoot::SetPosition(sf::Vector2f l_position)
{
	m_triangle.setPosition(sf::Vector2f(l_position.x / 2.f, l_position.y / 2.f));
}

sf::CircleShape* AngleShoot::GetShape()
{
	return &m_triangle;
}

bool AngleShoot::IsDead(UI& l_ui)
{
	return l_ui.GetHP() == 0 ? true : false;
}

std::vector<Bullet>* AngleShoot::GetVectorBullet()
{
	return &m_bulletAmmo;
}

void AngleShoot::Draw(sf::RenderWindow& l_target)
{

	for (auto itr = m_bulletAmmo.begin(); itr != m_bulletAmmo.end(); ++itr)
	{
		l_target.draw(*itr->GetShape());
	}
	l_target.draw(m_triangle);
}