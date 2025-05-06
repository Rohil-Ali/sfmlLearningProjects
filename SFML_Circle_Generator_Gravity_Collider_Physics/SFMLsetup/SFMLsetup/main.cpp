#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include "Circle.h"
#include "Collider.h"

int main()
{
	int width = 1100; //window width
	int height = 900; //window height
	sf::Clock clock; //clock to measure time
	sf::Clock holdTimer;
	std::srand(static_cast<unsigned int>(std::time(nullptr))); 
	sf::RenderWindow window(sf::VideoMode(width, height), "Circle Generator", sf::Style::Default);

	bool isMousePressed = false; // Flag to check if mouse is pressed
	bool hasSpawned = false; // Flag to check if a circle has been spawned

	Circle circleShape;
	//circleShape.createCircle(20); 
	
	//Game loop
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds(); 
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			//Event handling
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					circleShape.createCircle(1, evnt.mouseButton.x, evnt.mouseButton.y); // Create a new circle on mouse click
				}
				if (evnt.mouseButton.button == sf::Mouse::Right)
				{
					holdTimer.restart(); // Restart the hold timer	
					isMousePressed = true; // Set the flag to true when mouse is pressed
					hasSpawned = false;
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (evnt.mouseButton.button == sf::Mouse::Right)
				{
					isMousePressed = false; // Set the flag to false when mouse is released
					hasSpawned = false; 
				}
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isMousePressed && !hasSpawned)
		{
			if (holdTimer.getElapsedTime().asSeconds() >= 1.0f)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				circleShape.createCircle(10, static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
				hasSpawned = true; 
			}
		}

		window.clear();
		circleShape.moveCircles(deltaTime, width, height, window);

	
		
		for (int i = 0; i < circleShape.balls.size(); i++)
		{
			for (int j = i + 1; j < circleShape.balls.size(); j++)
			{
				Collider collider1(circleShape.balls[i].circle, circleShape.balls[i].velocity);
				Collider collider2(circleShape.balls[j].circle, circleShape.balls[j].velocity);
				collider1.checkCollision(collider2, 0.5f);
			}
		}


		
		window.display();
	}
}
