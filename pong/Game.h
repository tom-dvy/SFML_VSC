#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

class Game
{
public:
    Game();
    void start();
private:
    sf::RenderWindow window;
    Ball ball;
    Paddle leftPaddle;
    Paddle rightPaddle;
    int leftScore;
    int rightScore;
    sf::Font font;
    sf::Text leftScoreText;
    sf::Text rightScoreText;
    void init();
    void processEvents();
    void update();
    void render();
};

#endif // GAME_H