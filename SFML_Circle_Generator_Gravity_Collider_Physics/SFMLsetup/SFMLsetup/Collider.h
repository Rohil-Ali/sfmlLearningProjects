#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::CircleShape& circle, sf::Vector2f& velocity);
	~Collider();
	void checkCollision(Collider& other, float push);

private:
	sf::CircleShape& circle;
	sf::Vector2f& velocity;
};

