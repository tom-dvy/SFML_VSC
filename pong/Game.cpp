#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

// --- Constructor ---
Game::Game() : ball(), leftPaddle(20.f, 250.f), rightPaddle(770.f, 250.f)
{
    //std::cout << "Game constructor called !" << std::endl;
    init();
}

std::string getAppPath()
{
    char cExeFilePath[256];

    GetModuleFileNameA(NULL, cExeFilePath, 256);
    std::string exeFilePath = cExeFilePath;

    int exeNamePos = exeFilePath.find_last_of("\\/");
    std::string appPath = exeFilePath.substr(0, exeNamePos + 1);
    return appPath;
}

std::string getAssetsPath()
{
    return getAppPath() + "Assets\\";
}

void Game::init()
{
    leftScore = 0;
    rightScore = 0;
    
    if (!font.loadFromFile(getAssetsPath() + "ka1.ttf"))
    {
        std::cout << "Error loading font !" << std::endl;
    }

    leftScoreText.setFont(font);
    leftScoreText.setCharacterSize(30);
    leftScoreText.setFillColor(sf::Color::White);
    leftScoreText.setPosition(300.f, 10.f);
    leftScoreText.setString(std::to_string(leftScore));

    rightScoreText.setFont(font);
    rightScoreText.setCharacterSize(30);
    rightScoreText.setFillColor(sf::Color::White);
    rightScoreText.setPosition(500.f, 10.f);
    rightScoreText.setString(std::to_string(rightScore));
}

// --- Start the game ---
void Game::start()
{
    // --- Create the main window ---
    window.create(sf::VideoMode(800, 600), "Pong Game");
    window.setFramerateLimit(60);

    // --- Start the game loop ---
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

// --- Update the game state ---
void Game::update()
{
    ball.update();

    // Collisions
    if (ball.getBounds().intersects(leftPaddle.getBounds()) || ball.getBounds().intersects(rightPaddle.getBounds()))
    {
        ball.reverseX();
    }

    // --- Scoring ---
    if (ball.getBounds().left < 0)
    {
        std::cout << "Right player scores !" << std::endl;
        rightScore += 1;
        rightScoreText.setString(std::to_string(rightScore));
        ball = Ball();
        Sleep(1000);
    }
    else if (ball.getBounds().left + ball.getBounds().width > 800)
    {
        std::cout << "Left player scores !" << std::endl;
        leftScore += 1;
        leftScoreText.setString(std::to_string(leftScore));
        ball = Ball();
        Sleep(1000);
    }

}

// --- Process events ---
void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.key.code == sf::Keyboard::R)
            {
                init();
                ball = Ball();
            }
            
            // --- Left Player ---
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                leftPaddle.update(-2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                leftPaddle.update(2);
            
            // --- Right Player ---
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                rightPaddle.update(-2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                rightPaddle.update(2);
        }
    }
}

// --- Render of the game ---
void Game::render()
{
    window.clear();

    ball.display(window);

    leftPaddle.display(window);
    rightPaddle.display(window);    

    window.draw(leftScoreText);
    window.draw(rightScoreText);

    window.display();
}