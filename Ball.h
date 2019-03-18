#pragma once

#include <SFML\Graphics.hpp>
#include <random>

#define HEIGHT 800
#define WIDTH 1200
#define RAD 20

class Ball
{
public:
	sf::Vector2f pos;
	sf::Vector2f vel;
	int colour;
	float mass;

	Ball(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		vel.x = rand() % 20 - 10;
		vel.y = rand() % 20 - 10;
		mass = rand() % 5 + 1;
		colour = rand() % 3;
	}

	void Update(float time)
	{
		pos.x += vel.x * time;
		pos.y += vel.y * time;
		if (((pos.x > WIDTH - RAD) && (vel.x > 0)) || ((pos.x < RAD) && (vel.x < 0)))
		{
			vel.x = -vel.x;
		}
		if (((pos.y > HEIGHT - RAD) && (vel.y > 0)) || ((pos.y < RAD) && (vel.y < 0)))
		{
			vel.y = -vel.y;
		}
	}
};
