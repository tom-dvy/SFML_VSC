#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
public:
    Ball();
    void update();
    void display(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reverseX();
    void reverseY();
private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speedX;
    float speedY;
};

#endif // BALL_H