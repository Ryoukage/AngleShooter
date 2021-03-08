#pragma once
#include "Object.h"

class WorldCollision
{
public:
	WorldCollision();
	~WorldCollision();

	void Update(Object& l_obs, AngleShoot& l_as, UI& l_ui ,sf::Time time);
	
private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
};

