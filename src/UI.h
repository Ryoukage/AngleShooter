#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

 
class UI
{
	friend class WorldCollision;
	friend class Object;
	friend class AngleShoot;
public:
	UI();
	~UI();

	void Update(sf::Time time);
	void SetHit(bool l_hit);

	int GetHP();

	void Draw(sf::RenderWindow& l_window);

private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_comboText;
	sf::Text m_hpText;
	sf::Text m_waveText;
	sf::Text m_gameOverText;
	sf::Text m_comboEffectText;

	sf::RectangleShape m_waveBar;
	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_coreWindow;

	bool m_hit;
	bool m_isFadeOut;

	int m_score;
	int m_combo;
	int m_hp;
	int m_waveCount;

	float m_spawnObjectTime;
	float m_timeToNextWave;
	float m_fadeOutTime;
	float m_shootCooldown;

	std::vector<std::string>m_comboEffectTextString;

};

