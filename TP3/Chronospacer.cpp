#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <time.h>

const double PI = 3.14159265358979323846;

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chrono Spacer");

    GameState gameState = WaitingStart;
    
    srand(time(NULL));
    int timeToFind = (float)(rand() % (10 + 1));

    int WinInterval = 1;

    float turnPerSecond = 0.2f;

    // --- Circle ---
    // sf::CircleShape circle;
    // circle.setRadius(100.0f);
    // circle.setPosition(400.0f, 300.0f);
    // circle.setFillColor(sf::Color::Red);

    // --- Debug paths ---
    std::cout << "Chemin de l'app : " << getAppPath() << std::endl;
    std::cout << "Chemin des assets : " << getAssetsPath() << std::endl;

    // --- Text ---
    sf::Font font;
    if (!font.loadFromFile(getAssetsPath() + "Game Of Squids.ttf"))
    {
        std::cout << "Failed to load font !" << std::endl;
        return -1;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Chrono Spacer");
    title.setPosition(200.0f, 50.0f);
    title.setCharacterSize(50);

    sf::Text rules;
    rules.setFont(font);
    rules.setString("Press SPACEBAR to start the game.\nPress ECHAP to quit the game.\nCount to " + std::to_string(timeToFind) +" then press SPACEBAR.");
    rules.setPosition(10.0f, 200.0f);
    rules.setCharacterSize(20);

    // --- Texture ---
    sf::Texture texture;
    if (!texture.loadFromFile(getAssetsPath() + "space.png"))
    {
        std::cout << "Failed to load texture !" << std::endl;
        return -1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(400.0f, 300.0f);

    // --- Time ---
    sf::Clock clock;

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
                if (event.key.code == sf::Keyboard::Space)

                    switch (gameState)
                    {
                    case WaitingStart:
                        gameState = Timing;
                        rules.setString("Press SPACEBAR to stop");
                        clock.restart();
                        break;

                    case Timing:
                    {
                        float deltaTime = clock.getElapsedTime().asSeconds();

                        gameState = Finished;

                        if (deltaTime >= timeToFind - WinInterval && deltaTime <= timeToFind + WinInterval)
                        {
                            rules.setString("You won !\nNew win interval : " + std::to_string(WinInterval * 0.2f) + " seconds.");
                            WinInterval *= 0.2f;
                        }
                        else
                        {
                            rules.setString("You lost !\nThe target time was " + std::to_string(timeToFind) + " seconds.");
                        }
                    }
                    break;

                    case Finished:
                    {
                        // Reset the game
                        gameState = WaitingStart;
                        timeToFind = (float)(rand() % (10 + 1));
                        rules.setString("Press SPACEBAR to restart\nCount to " + std::to_string(timeToFind) +" then press SPACEBAR.");
                        break;
                    }
                    }

                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        /*switch (gameState)
        {
        case WaitingStart:

            break;

        case Timing:

            break;

        case Finished:

            break;

        default:
            break;
        }*/

        // float deltaAngle = deltaTime * PI * 2.0f * turnPerSecond;
        // sprite.rotate(deltaAngle);

        sf::Vector2u textureSize = texture.getSize();
        sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
        
        window.clear();
        window.draw(sprite);
        window.draw(title);
        window.draw(rules);
        window.display();
    }

    return 0;
}