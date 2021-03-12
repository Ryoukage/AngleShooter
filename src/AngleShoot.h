#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Bullet.h"
#include "UI.h"
#include "ColorSet.h"
#include "SoundResource.h"
#include <vector>
#include <iostream>


class AngleShoot
{
	friend class WorldCollision;
public:
	AngleShoot();
	~AngleShoot();

	void SetRotation(float l_rotation);
	void SetPosition(sf::Vector2f l_position);
	void Move(sf::Vector2f l_move);
	void Update(sf::Time time, UI& l_ui);
	void Shoot(double l_angle, double r_angle, UI& l_ui);
	void SetHit(bool l_hit);

	void ResetContainer();

	bool IsDead(UI& l_ui);

	bool GetHit()const;

	std::vector<Bullet>* GetVectorBullet();
	sf::CircleShape* GetShape();

	void Draw(sf::RenderWindow& l_target);

protected:
	std::vector<Bullet>m_bulletAmmo;

private:
	sf::SoundBuffer m_shootSoundBuffer;
	sf::Sound m_shootSound;
	sf::CircleShape m_triangle;
	ColorSet m_color;

	bool m_hit;

	float m_coolDownTime;
	float m_shootTime;
};

