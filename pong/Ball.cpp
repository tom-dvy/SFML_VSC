#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// --- Constructor ---
Ball::Ball()
{
    //std::cout << "Ball constructor called !" << std::endl;

    shape.setRadius(10);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(400.f, 300.f);
    speedX = 3.f;
    speedY = 3.f;
}

// --- Start the ball movement ---
void Ball::update()
{
    shape.move(speedX, speedY);
    if (shape.getPosition().x < 0 || shape.getPosition().x > 790)
    {
        reverseX();
    }
    
    if (shape.getPosition().y < 0 || shape.getPosition().y > 590)
    {
        reverseY();
        /*speedX = speedX + 0.2f;
        speedY = speedY + 0.2f;
        std::cout << "speedX : " << speedX << " | speedY : " << speedY << std::endl;*/
    }
    
}

// --- Display the ball ---
void Ball::display(sf::RenderWindow& window)
{
    window.draw(shape);
}

// --- Reverse the ball on X ---
void Ball::reverseX()
{
    speedX = -speedX;
}

// --- Reverse the ball on Y ---
void Ball::reverseY()
{
    speedY = -speedY;
}

// --- Get the ball bounds ---
sf::FloatRect Ball::getBounds() const
{
    return shape.getGlobalBounds();
}