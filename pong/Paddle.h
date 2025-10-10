#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle
{
public:
    Paddle(float posX, float posY);
    void update(float direction);
    sf::FloatRect getBounds() const;
    void display(sf::RenderWindow& window);
private:
    sf::RectangleShape shape;;
    float speed;
};

#endif // PADDLE_H