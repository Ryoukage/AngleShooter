#include "WorldCollision.h"

WorldCollision::WorldCollision()
{
	if (!m_buffer.loadFromFile("fun_1.wav"))
	{

	}
	m_sound.setBuffer(m_buffer);
}

WorldCollision::~WorldCollision(){}

void WorldCollision::Update(Object& l_obj, AngleShoot& l_as,UI& l_ui, sf::Time time)
{
	for (auto itr = l_obj.m_objectGroup.begin(); itr != l_obj.m_objectGroup.end(); ++itr)
	{
		for (auto it = l_as.m_bulletAmmo.begin(); it != l_as.m_bulletAmmo.end(); ++it)
		{
			if (itr->GetShape()->getPosition().x + itr->GetShape()->getOrigin().x > it->GetShape()->getPosition().x&&
				itr->GetShape()->getPosition().x - itr->GetShape()->getOrigin().x<it->GetShape()->getPosition().x &&
				itr->GetShape()->getPosition().y + itr->GetShape()->getOrigin().y > it->GetShape()->getPosition().y &&
				itr->GetShape()->getPosition().y - itr->GetShape()->getOrigin().y < it->GetShape()->getPosition().y&&!itr->m_isCollision)
			{
				if (itr->GetShape()->getFillColor() == it->GetShape()->getFillColor()) {
					itr->SetCollision(true);
					it->SetCollision(true);
					itr->m_velocity.x = 0.f;
					itr->m_velocity.y = 0.f;
					itr->m_particle.setEmitter(itr->GetShape()->getPosition());
					itr->m_particle.SetColor(itr->GetShape()->getFillColor());
					l_ui.SetHit(true);
					m_sound.play();
				}
				else
				{
					it->GetText()->setFillColor(sf::Color(255, 255, 255, 255));
					it->GetText()->setFillColor(it->GetShape()->getFillColor());
					it->GetText()->setPosition(it->GetShape()->getPosition());
					it->SetMiss(true);
					it->SetColor(it->GetShape()->getFillColor());
				}
			}
		}
	}

	for (auto at = l_obj.m_objectGroup.begin(); at != l_obj.m_objectGroup.end(); ++at)
	{
		if (at->GetCollision())
		{
			at->m_particle.update(time);
			at->m_timeToDeath -= time.asSeconds();
			at->GetShape()->setFillColor(sf::Color(255, 255, 255, 0));
		}
		if (at->m_timeToDeath <= 0.f)
		{
			at->SetErase(true);
		}
	}

	l_obj.m_objectGroup.erase(std::remove_if(l_obj.m_objectGroup.begin(), l_obj.m_objectGroup.end(), [](Object& aloc)->bool
		{
			return aloc.GetErase();
		}), l_obj.m_objectGroup.end());

	l_as.m_bulletAmmo.erase(std::remove_if(l_as.m_bulletAmmo.begin(), l_as.m_bulletAmmo.end(), [](Bullet& aloc)->bool
		{
			return aloc.GetCollision();
		}), l_as.m_bulletAmmo.end());
}

