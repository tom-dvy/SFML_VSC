#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// --- Constructor ---
Paddle::Paddle(float posX, float posY)
{
    //std::cout << "Paddle constructor called !" << std::endl;

    shape.setSize(sf::Vector2f(10, 100));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(posX, posY);
    speed = 5.f;
}

// --- Start the paddle movement ---
void Paddle::update(float direction)
{
    shape.move(0, direction * speed);
    if ((shape.getPosition().y < 0) || (shape.getPosition().y > 800))
    {
        shape.move(0, -direction* speed);
    }
}

// --- Display the paddle ---
void Paddle::display(sf::RenderWindow& window)
{
    window.draw(shape);
}

// --- Get the paddle bounds ---
sf::FloatRect Paddle::getBounds() const
{
    return shape.getGlobalBounds();
}