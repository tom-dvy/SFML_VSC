#ifndef PARTICULESMANAGER_H
#define PARTICULESMANAGER_H

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <list>
#include <iostream>
#include <vector>

class ParticulesManager
{
public:
    ParticulesManager();

    struct sParticle {
        float timeToLive;
        float elapsedTime = 0;

        sf::CircleShape shape;
    };
    struct sParticleSystem {
        std::list<sParticle> existingParticles;
        float creationPeriod;
        float chronoCreation = 0;
        float minLifeTime;
        float maxLifeTime;
        sf::Vector2f origin;
        float spawnRadius;
        float particleSize;
    };

    void AddParticleToSystem(sParticleSystem* particleSystem, float timeToLive);
    void UpdateParticleSystem(sParticleSystem* particleSystem, float deltaTime);
    void ClearParticleSystem(sParticleSystem* particleSystem);
    sParticleSystem CreateParticleSystem(float creationPeriod, float minLifeTime, float maxLifeTime, sf::Vector2f origin, float spawnRadius, float particleSize);
    void DrawParticleSystem(sParticleSystem& particlesystem, sf::RenderWindow& window);
};

#endif // PARTICULESMANAGER_H