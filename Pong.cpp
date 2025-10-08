#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <time.h>

// --- Game state ---
enum GameState
{
    WaitingStart,
    Timing,
    Finished
};

// --- Functions ---
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

int main()
{
    // --- Window ---
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Pong");

    GameState gameState = WaitingStart;

    // --- Debug paths ---
    std::cout << "Chemin de l'app : " << getAppPath() << std::endl;
    std::cout << "Chemin des assets : " << getAssetsPath() << std::endl;

    // --- Text ---
    sf::Font font;
    if (!font.loadFromFile(getAssetsPath() + "ka1.ttf"))
    {
        std::cout << "Failed to load font !" << std::endl;
        return -1;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Pong");
    title.setPosition(400, 50);
    title.setCharacterSize(50);

    sf::Text rules;
    rules.setFont(font);
    rules.setString("Press SPACEBAR to start the game !\nPress ECHAP to quit the game !");
    rules.setPosition(30, 200);
    rules.setCharacterSize(20);

    sf::RectangleShape leftPlayer;
    leftPlayer.setSize(sf::Vector2f(25.0f, 100.0f));
    leftPlayer.setPosition(50.0f, 300.0f);

    sf::RectangleShape rightPlayer;
    rightPlayer.setSize(sf::Vector2f(25.0f, 100.0f));
    rightPlayer.setPosition(725.0f, 300.0f);

    sf::CircleShape ball;
    ball.setRadius(15);

    // --- Main loop ---
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // --- Keyboard input ---
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw(title);
        window.draw(rules);

        window.display();
    }
}