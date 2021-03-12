#include "Object.h"



Object::Object(MainMenu& l_mainMenu) :m_coolDownTarget(2.5f)
{
	m_colorSet.push_back(sf::Color::Red);
	m_colorSet.push_back(sf::Color::Green);
	m_colorSet.push_back(sf::Color::Blue);
	m_ptrMainMenu = &l_mainMenu;
}

Object::Object(sf::Vector2f l_velocity, sf::Vector2f l_size, sf::Color l_color, sf::Vector2f l_position) : m_velocity(l_velocity), m_hit(false), m_isCollision(false), m_particle(1000), m_timeToDeath(2.f),m_erase(false)
{
	m_shape.setSize(l_size);
	m_shape.setFillColor(l_color);
	m_shape.setPosition(l_position);
	m_shape.setOrigin(sf::Vector2f(l_size.x / 2.f, l_size.y / 2.f));

	m_ptrMainMenu = nullptr;
}

Object::~Object()
{
	
}

void Object::SetHit(bool l_hit)
{
	m_hit = l_hit;
}

bool Object::GetHit()const
{
	return m_hit;
}

void Object::SetCollision(bool l_collision)
{
	m_isCollision = l_collision;
}

bool Object::GetCollision()const
{
	return m_isCollision;
}

void Object::SetErase(bool l_erase)
{
	m_erase = l_erase;
}

bool Object::GetErase()const
{
	return m_erase;
}

void Object::Draw(sf::RenderWindow& l_window)
{
	for (auto itr = m_objectGroup.begin(); itr != m_objectGroup.end(); ++itr)
	{
		l_window.draw(itr->m_shape);
		l_window.draw(itr->m_particle);
	}
}

void Object::Update(sf::Time time,UI& l_ui)
{
	m_cooldownSpawn += time.asSeconds();
	if (m_cooldownSpawn > l_ui.m_spawnObjectTime)
	{	
		//UP,LEFT,DOWN,RIGHT
		//DO OFFSET WINDOW
		sf::Vector2f areaSpawn[] = { sf::Vector2f(std::rand() % static_cast<int>(m_angleShoot.GetShape()->getPosition().x * 2.f),0.f),sf::Vector2f(0.f,std::rand() % static_cast<int>(m_angleShoot.GetShape()->getPosition().y * 2)),
										sf::Vector2f(std::rand() % static_cast<int>(m_angleShoot.GetShape()->getPosition().x * 2.f),m_angleShoot.GetShape()->getPosition().y * 2.f),
										sf::Vector2f((m_angleShoot.GetShape()->getPosition().x * 2.f) + 150.f,std::rand() % static_cast<int>(m_angleShoot.GetShape()->getPosition().y * 2.f)) };
		Spawn(sf::Vector2f(areaSpawn[std::rand() % 4]));
		m_cooldownSpawn = 0.f;
	}
	for (auto itr = m_objectGroup.begin(); itr != m_objectGroup.end(); ++itr)
	{
		itr->m_shape.rotate(190 * time.asSeconds());
		itr->m_shape.move(itr->m_velocity.x * time.asSeconds() * 60, itr->m_velocity.y * time.asSeconds() * 60);
		//DO OFFSET WINDOW
		if (itr->m_shape.getPosition().x > m_angleShoot.GetShape()->getPosition().x + 50.f && itr->m_shape.getPosition().x < m_angleShoot.GetShape()->getPosition().x + 100.f
			&& itr->m_shape.getPosition().y>m_angleShoot.GetShape()->getPosition().y - 25.f && itr->m_shape.getPosition().y < m_angleShoot.GetShape()->getPosition().y + 50.f)
		{
			itr->SetHit(true);
			l_ui.m_combo = 0;
			if(m_ptrMainMenu->GetStart())
				l_ui.m_hp-=5;
		}
	}
	m_objectGroup.erase(std::remove_if(m_objectGroup.begin(), m_objectGroup.end(), [](Object& aloc)->bool
		{
			return aloc.GetHit();
		}), m_objectGroup.end());
}

void Object::Spawn(sf::Vector2f l_position)
{
	//DO OFFSET WINDOW
	sf::Vector2f dir = sf::Vector2f((m_angleShoot.GetShape()->getPosition().x + 100) - l_position.x, (m_angleShoot.GetShape()->getPosition().y - 20) - l_position.y);
	auto vector = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
	double dX = dir.x / vector;
	double dY = dir.y / vector;
	m_objectGroup.push_back(Object(sf::Vector2f(dX, dY), sf::Vector2f(50.f, 50.f), m_colorSet[std::rand() % 3], l_position));
}

void Object::ResetContainer()
{
	m_objectGroup.clear();
}

std::vector<Object>* Object::GetVector()
{
	return &m_objectGroup;
}

sf::RectangleShape* Object::GetShape()
{
	return &m_shape;
}
