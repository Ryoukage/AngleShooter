#include "UI.h"


UI::UI() :m_score(0), m_combo(0), m_hp(100), m_waveCount(1), m_timeToNextWave(10.f), m_spawnObjectTime(2.5f), m_fadeOutTime(0), m_isFadeOut(false), m_shootCooldown(1.5f)
{
	if (!m_font.loadFromFile("slkscr.ttf"))
	{
		std::cout << "Cant load the font !" << std::endl;
	}

	m_comboEffectTextString.push_back("NICE");
	m_comboEffectTextString.push_back("EXCELLENT");
	m_comboEffectTextString.push_back("GOOD");

	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::White);
	m_text.setString("Score : " + std::to_string(m_score));
	m_text.setStyle(sf::Text::Bold);
	m_text.setPosition(10.f, 10.f);

	m_comboText.setFont(m_font);
	m_comboText.setCharacterSize(72);
	m_comboText.setFillColor(sf::Color::White);
	m_comboText.setString(std::to_string(m_combo));
	m_comboText.setStyle(sf::Text::Bold);
	m_comboText.setPosition({ 650.f,0.f });

	m_comboEffectText.setFont(m_font);
	m_comboEffectText.setCharacterSize(60);
	m_comboEffectText.setFillColor(sf::Color(255, 255, 255, 0));
	m_comboEffectText.setString(m_comboEffectTextString[1]);
	m_comboEffectText.setStyle(sf::Text::Bold);
	m_comboEffectText.setPosition(15.f, 660.f);

	m_hpText.setFont(m_font);
	m_hpText.setCharacterSize(30);
	m_hpText.setFillColor(sf::Color::White);
	m_hpText.setString("HP");
	m_hpText.setStyle(sf::Text::Bold);
	m_hpText.setPosition(15.f, 300.f);

	m_waveText.setFont(m_font);
	m_waveText.setCharacterSize(30);
	m_waveText.setFillColor(sf::Color::White);
	m_waveText.setString("Wave " + std::to_string(m_waveCount) + " : ");
	m_waveText.setStyle(sf::Text::Bold);
	m_waveText.setPosition(475.f, 690.f);

	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(128);
	m_gameOverText.setFillColor(sf::Color::White);
	m_gameOverText.setString("Game Over !!!");
	m_gameOverText.setStyle(sf::Text::Bold);
	m_gameOverText.setPosition(185.f, 310.f);

	m_healthBar.setPosition({ 20.f,300.f });
	m_healthBar.setSize({ 20.f,-2.f * m_hp });
	m_healthBar.setFillColor(sf::Color::White);

	m_coreWindow.setSize({ 1366,720 });
	m_coreWindow.setFillColor(sf::Color(0, 0, 0, 125));

	m_waveBar.setSize({ 20.f * m_timeToNextWave,20.f });
	m_waveBar.setPosition({ 660.f,700.f });
	m_waveBar.setFillColor(sf::Color::White);

	m_textEffect.setFont(m_font);
	m_textEffect.setCharacterSize(24);
	m_textEffect.setString("Miss !");
	m_textEffect.setStyle(sf::Text::Bold);
	m_textEffect.setFillColor(sf::Color(255, 255, 255, 0));


}

void UI::Draw(sf::RenderWindow& l_window)
{
	l_window.draw(m_text);
	l_window.draw(m_comboText);
	l_window.draw(m_healthBar);
	l_window.draw(m_hpText);
	l_window.draw(m_waveText);
	l_window.draw(m_waveBar);
	l_window.draw(m_comboEffectText);
	if (m_hp == 0)
	{
		l_window.draw(m_coreWindow);
		l_window.draw(m_gameOverText);
	}
}

void UI::Update(sf::Time time)
{
	if (m_hit)
	{
		m_combo++;
		m_score += 50 * m_combo * 0.75;

		m_hit = false;
		
	}
	m_timeToNextWave -= time.asSeconds();

	if (m_timeToNextWave < 0)
	{
		m_timeToNextWave = 10.f;
		m_spawnObjectTime -= 0.075f;
		m_shootCooldown -= 0.050f;
		m_waveCount++;
	}

	switch (m_hp)
	{
	case 75:
		m_healthBar.setFillColor(sf::Color(255, 195, 77));
		break;
	case 50:
		m_healthBar.setFillColor(sf::Color(255, 159, 0));
		break;
	case 25:
		m_healthBar.setFillColor(sf::Color(255, 129, 0));
		break;
	case 10:
		m_healthBar.setFillColor(sf::Color(255, 64, 35));
	default:
		break;
	}

	if (m_combo % 5 == 0 && m_combo != 0 && !m_isFadeOut)
	{
		m_comboEffectText.setString(m_comboEffectTextString[std::rand() % m_comboEffectTextString.size()]);
		m_comboEffectText.setFillColor(sf::Color(255, 255, 255, 255));
		m_fadeOutTime = 1.f;
		m_isFadeOut = true;
	}

	if (m_fadeOutTime <= 1.5f && m_fadeOutTime > 0)
	{
		m_fadeOutTime -= time.asSeconds();
		m_comboEffectText.setFillColor(sf::Color(255, 255, 255, 255 * m_fadeOutTime));
	}

	if (m_combo % 5 == 1 && m_combo != 1)
	{
		m_isFadeOut = false;
	}


	m_text.setString("Score : " + std::to_string(m_score));
	m_comboText.setString(std::to_string(m_combo));
	m_healthBar.setSize({ 20.f,-2.f * m_hp });
	m_waveBar.setSize({ 20.f * m_timeToNextWave,20.f });
	m_waveText.setString("Wave " + std::to_string(m_waveCount) + " : ");
}

void UI::SetHit(bool l_hit)
{
	m_hit = l_hit;
}

sf::Text UI::GetText()
{
	return m_textEffect;
}

int UI::GetHP()
{
	return m_hp;
}

UI::~UI()
{

}
