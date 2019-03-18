#include <SFML\Graphics.hpp>
#include <math.h>
#include <vector>
#include "Ball.h"

void BumpBalls(std::vector<Ball> &balls, int i, int j);

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window");
	window.setFramerateLimit(80);

	sf::Clock clock;
	std::vector<sf::Color> colours;
	colours.push_back(sf::Color::Red);
	colours.push_back(sf::Color::Blue);
	colours.push_back(sf::Color::Green);
	std::vector<Ball> balls;

	sf::CircleShape circle(RAD);
	circle.setOrigin(RAD, RAD);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					sf::Vector2i mouse_pos= sf::Mouse::getPosition(window);
					Ball ball(mouse_pos.x, mouse_pos.y);
					balls.push_back(ball);
				}
			}
		}
		
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		for (auto &it : balls)
		{
			it.Update(time * 50);
		}
		
		for (int i = 0; i < balls.size(); i++)
		{
			for (int j = i + 1; j < balls.size(); j++)
			{
				BumpBalls(balls, i, j);
			}
		}
		
		window.clear();
		for (auto it : balls)
		{
			circle.setFillColor(colours[it.colour]);
			circle.setPosition(it.pos.x, it.pos.y);
			window.draw(circle);
		}
		window.display();
	 }

	return 0;
}

void BumpBalls(std::vector<Ball> &balls, int i, int j)
{
	float len = sqrt((pow((balls[i].pos.x - balls[j].pos.x), 2) + pow((balls[i].pos.y - balls[j].pos.y), 2)));
	if (len <= 2 * RAD)
	{
		sf::Vector2f d(balls[i].pos.x - balls[j].pos.x, balls[i].pos.y - balls[j].pos.y);
		if (((balls[j].vel.x * d.x + balls[j].vel.y * d.y) - (balls[i].vel.x * d.x + balls[i].vel.y * d.y)) > 0)
		{
			sf::Vector2f norm(d.x / len, d.y / len);
			sf::Vector2f delta = (2 * ((balls[j].vel.x * norm.x + balls[j].vel.y * norm.y) - (balls[i].vel.x * norm.x + balls[i].vel.y * norm.y)) / (1 / balls[i].mass + 1 / balls[j].mass)) * norm;
			balls[i].vel += delta / balls[i].mass;
			balls[j].vel -= delta / balls[j].mass;
		}
	}
}
