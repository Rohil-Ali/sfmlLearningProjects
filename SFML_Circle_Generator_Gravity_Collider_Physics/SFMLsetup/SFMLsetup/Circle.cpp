#include "Circle.h"

Circle::Circle()
{
}

Circle::~Circle()
{
}

void Circle::createCircle(int numberOfBalls, float mouseX, float mouseY)
{
	for (int i = 0; i < numberOfBalls; i++)
	{
		float radius = rand() % 20 + 10; //random radius
		sf::CircleShape circle(radius); //random size
		circle.setOrigin(radius, radius); //set origin to center
		circle.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1)); //random color 
		circle.setPosition(mouseX, mouseY);

		float x = (rand() % 1601) - 800.0f;  // Range: [-800, 800]
		float y = (rand() % 1601) - 800.0f;  // Range: [-800, 800]

		sf::Vector2f velocity(x, y);

		Ball b{ circle, velocity };
		balls.push_back(b); // Add the ball struct to the vector
	}
}

void Circle::moveCircles(float deltaTime, int width, int height, sf::RenderWindow& window)
{
	float gravity = 500.0f;

	for (auto& circle : balls)
	{
		circle.velocity.y += gravity * deltaTime; // Apply gravity to the y velocity

		circle.circle.move(circle.velocity * deltaTime); // Move the circle

		float radius = circle.circle.getRadius();

		if (circle.circle.getPosition().x - radius <= 0)
		{
			circle.circle.setPosition(radius, circle.circle.getPosition().y); // Set position to radius/2
			circle.velocity.x = -circle.velocity.x; // Reverse x direction
		}
		if (circle.circle.getPosition().x + radius >= width)
		{
			circle.circle.setPosition(width - radius, circle.circle.getPosition().y); // Set position to width - radius/2
			circle.velocity.x = -circle.velocity.x; // Reverse x direction
		}

		if (circle.circle.getPosition().y - radius <= 0)
		{
			circle.circle.setPosition(circle.circle.getPosition().x, radius); // Set position to radius/2
			circle.velocity.y = -circle.velocity.y; // Reverse y direction
		}
		if (circle.circle.getPosition().y + radius >= height)
		{
			circle.circle.setPosition(circle.circle.getPosition().x, height - radius); // Set position to height - radius/2
			circle.velocity.y = -circle.velocity.y * 0.8f; // Reverse y direction
			circle.velocity.x *= 0.9f; // Apply air resistance to the x velocity
		}
		
		window.draw(circle.circle); // Draw the circle
	}
}
