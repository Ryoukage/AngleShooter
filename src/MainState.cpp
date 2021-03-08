#include "WorldCollision.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Angle Shooter",sf::Style::Titlebar);
	AngleShoot shoot;
	Object object;
	WorldCollision worldCollision;
	UI ui;

	sf::Music music;
	music.openFromFile("Intense.ogg");
	music.setLoop(true);
	music.play();

	sf::Clock clock;
	
	const float rotationSpeed = 500.f;
	
	sf::Vector2f dir;
	
	float timeElapsed = 0.f;

	shoot.SetPosition(static_cast<sf::Vector2f>(window.getSize()));
	while (window.isOpen())
	{
		auto mouse = sf::Mouse::getPosition(window);
		float angle = -std::atan2(mouse.x - shoot.GetShape()->getPosition().x, mouse.y - shoot.GetShape()->getPosition().y) * (180 / 3.14);
		dir = (static_cast<sf::Vector2f>(mouse) - (shoot.GetShape()->getPosition()));
		auto vectorLen = std::sqrt(pow(dir.x, 2) + pow(dir.y, 2));
		double dx = dir.x / vectorLen;
		double dy = dir.y / vectorLen;

		sf::Event event;
		sf::Time time = clock.restart();

		if (!shoot.IsDead(ui)) {
			shoot.Update(time, ui);
			object.Update(time, ui);
			worldCollision.Update(object, shoot, ui, time);
			ui.Update(time);
		}

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Insert)
				{
					window.close();
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				{
					shoot.Shoot(dx, dy);
				}
			}
		window.clear(sf::Color::Black);
		shoot.SetRotation(180 + angle);
		shoot.Draw(window);
		object.Draw(window);
		ui.Draw(window);

		window.display();
	}
}