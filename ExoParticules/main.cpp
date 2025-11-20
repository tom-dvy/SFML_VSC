#include <SFML/Graphics.hpp>
#include "ParticulesManager.h"
#include <iostream>
#include <list>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle System");
    window.setFramerateLimit(60);

    sf::Clock clock;
    ParticulesManager manager;

    ParticulesManager::sParticleSystem mySystem = manager.CreateParticleSystem(2, 2, 5, sf::Vector2f(400, 300), 100, 5);
    manager.AddParticleToSystem(&mySystem, 3);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
        }
        
        
        float deltaTime = clock.restart().asSeconds();

        manager.UpdateParticleSystem(&mySystem, deltaTime);

        window.clear();

        manager.DrawParticleSystem(mySystem, window);

        window.display();
    }
    

    /*
    std::list<float> floatList = {
        5.0f, 
        3.5f, 
        10.2f, 
        2.0f, 
        1.6f, 
        7.8f, 
        5.1f
    };

    std::list<float>::iterator i = floatList.begin();

    while (floatList.size() != 0)
    {
        
        for (auto &number : floatList)
        {
            number--;

            if (number <= 0.0f)
            {
                floatList.erase(i);
                i++;
            }
            std::cout << number << " n'a pas été supprimé" << std::endl;
        }

        system("pause");
    }
    */

    return 0;
}