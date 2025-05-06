#pragma once  
#include <SFML/Graphics.hpp>  
#include <vector>  

struct Ball // Define the struct Ball here  
{
    sf::CircleShape circle;
    sf::Vector2f velocity;
};

class Circle  
{  
public:   
   Circle();  
   ~Circle();  
   void createCircle(int numberOfBalls, float mouseX, float mouseY);
   void moveCircles(float deltaTime, int width, int height, sf::RenderWindow& window);
   std::vector<Ball> balls;  


private:  
};
