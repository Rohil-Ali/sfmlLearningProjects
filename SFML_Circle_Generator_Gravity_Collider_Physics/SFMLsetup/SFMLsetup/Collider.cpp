#include "Collider.h"

Collider::Collider(sf::CircleShape& circle, sf::Vector2f& velocity) : circle(circle), velocity(velocity)
{
}

Collider::~Collider()
{
}

void Collider::checkCollision(Collider& other, float push)
{
	//stores the positions of the circles
	sf::Vector2f posA = circle.getPosition();
	sf::Vector2f posB = other.circle.getPosition();

	//calculates the distance/delta between the circles
	float deltaX = posB.x - posA.x;
	float deltaY = posB.y - posA.y;
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	float combinedRadius = circle.getRadius() + other.circle.getRadius();

	//collision resolution
	if (distance < combinedRadius)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);
		float overlap = combinedRadius - distance;
		sf::Vector2f collisionDir = { deltaX / distance, deltaY / distance };
		circle.move(-collisionDir * overlap * (1.0f - push)); //lower the push higher the correction
		other.circle.move(collisionDir * overlap * push); //higher the push lower the correction
		std::swap(velocity, other.velocity); //swap the velocities
	}
}
