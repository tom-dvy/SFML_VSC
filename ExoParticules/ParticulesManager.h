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
        float moveSpeed;

        sf::CircleShape shape;
        sf::Vector2f direction;
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
        float frictionCoef = 0.5f;
        bool isPlaying = false;
        float systemLifeTime = 0.0f;
        float elapsedSystemTime = 0.0f;
        bool hasExploded = false;
    };
    std::vector<sParticleSystem> fireworkSystems;
    float fireworkSpawnTimer = 0.0f;
    float nextFireworkSpawn = 1.0f;


    void AddParticleToSystem(sParticleSystem* particleSystem, float timeToLive);
    void UpdateParticleSystem(sParticleSystem* particleSystem, float deltaTime);
    void ClearParticleSystem(sParticleSystem* particleSystem);
    sParticleSystem CreateParticleSystem(float creationPeriod, float minLifeTime, float maxLifeTime, sf::Vector2f origin, float spawnRadius, float particleSize);
    void DrawParticleSystem(sParticleSystem& particlesystem, sf::RenderWindow& window);
    void PlayParticleSystem(sParticleSystem* sParticleSystem);
    bool IsParticleSystemPlaying(sParticleSystem* particleSystem);
    void UpdateFireworks(float deltaTime);
    void DrawFireworks(sf::RenderWindow& window);

};

#endif // PARTICULESMANAGER_H