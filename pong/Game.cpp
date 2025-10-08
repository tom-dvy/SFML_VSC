#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// --- Constructor ---
Game::Game()
{
    std::cout << "Game constructor called !" << std::endl;
}

// --- Start the game ---
void Game::start()
{
    // Create the main window
    window.create(sf::VideoMode(800, 600), "Pong Game");
    window.setFramerateLimit(60);

    // Start the game loop
    while (window.isOpen())
    {
        processEvents();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::render()
{
    window.clear();

    window.display();
}