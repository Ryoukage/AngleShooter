#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "AngleShoot.h"
#include "Particle.h"
#include "MainMenu.h"
#include <vector>

class Object
{
	friend class WorldCollision;
public:
	Object(MainMenu& l_mainMenu);
	Object(sf::Vector2f l_velocity, sf::Vector2f l_size, sf::Color l_color, sf::Vector2f l_position);

	void Draw(sf::RenderWindow& l_window);
	void Update(sf::Time time,UI& l_ui);

	void SetHit(bool l_hit);
	bool GetHit()const;

	void SetCollision(bool l_collision);
	bool GetCollision()const;

	void SetErase(bool l_erase);
	bool GetErase()const;

	void ResetContainer();

	sf::RectangleShape* GetShape();

	~Object();
	void Spawn(sf::Vector2f l_position);

	std::vector<Object>* GetVector();


protected:
	std::vector<Object>m_objectGroup;

private:
	AngleShoot m_angleShoot;
	sf::RectangleShape m_shape;
	ParticleSystem m_particle;
	
	MainMenu* m_ptrMainMenu;

	std::vector<sf::Color>m_colorSet;

	sf::Vector2f m_velocity;

	float m_cooldownSpawn;
	float m_coolDownTarget;
	float m_timeToDeath;

	bool m_hit;
	bool m_isCollision;
	bool m_erase;

};

