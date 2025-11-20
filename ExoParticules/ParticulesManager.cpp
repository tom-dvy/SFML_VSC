#include "ParticulesManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.h"
#include <windows.h>

void ParticulesManager::AddParticleToSystem(sParticleSystem* particleSystem, float timeToLive)
{
    const float PI = 3.14159265f;
    
    sParticle newParticle;

    newParticle.timeToLive = timeToLive;
    newParticle.elapsedTime = 0;

    float angle = PI * 2.0f * (float)rand() / RAND_MAX;
    float distance = particleSystem->spawnRadius * sqrt((float)rand() / RAND_MAX);

    float x = particleSystem->origin.x + cos(angle) * distance;
    float y = particleSystem->origin.y + sin(angle) * distance;

    newParticle.shape.setRadius(particleSystem->particleSize);
    newParticle.shape.setOrigin(particleSystem->particleSize, particleSystem->particleSize);
    newParticle.shape.setPosition(x, y);
    newParticle.shape.setFillColor(sf::Color::White);

    particleSystem->existingParticles.push_back(newParticle);
}

void ParticulesManager::UpdateParticleSystem(sParticleSystem* particleSystem, float deltaTime)
{
    for (auto it = particleSystem->existingParticles.begin(); it != particleSystem->existingParticles.end(); )
    {
        it->elapsedTime += deltaTime;

        if (it->elapsedTime >= it->timeToLive)
        {
            it = particleSystem->existingParticles.erase(it);
        }
        else
        {
            ++it;
        }
    }
    particleSystem->chronoCreation += deltaTime;

    while (particleSystem->chronoCreation >= particleSystem->creationPeriod)
    {
        particleSystem->chronoCreation -= particleSystem->creationPeriod;

        sParticle newParticle;
        newParticle.timeToLive = particleSystem->minLifeTime
            + (particleSystem->maxLifeTime - particleSystem->minLifeTime)
                * (float)rand() / RAND_MAX;

        newParticle.elapsedTime = 0;
        particleSystem->existingParticles.push_back(newParticle);
    }
}


void ParticulesManager::ClearParticleSystem(sParticleSystem* particleSystem)
{
    particleSystem->existingParticles.clear();

    particleSystem->chronoCreation = 0;
}

ParticulesManager::sParticleSystem ParticulesManager::CreateParticleSystem(float creationPeriod, float minLifeTime, float maxLifeTime, sf::Vector2f origin, float spawnRadius, float particleSize)
{
    sParticleSystem newParticleSystem;

    newParticleSystem.creationPeriod = creationPeriod;
    newParticleSystem.minLifeTime = minLifeTime;
    newParticleSystem.maxLifeTime = maxLifeTime;

    newParticleSystem.origin = origin;
    newParticleSystem.spawnRadius = spawnRadius;
    newParticleSystem.particleSize = particleSize;

    return newParticleSystem;
}

void ParticulesManager::DrawParticleSystem(sParticleSystem& particleSystem, sf::RenderWindow& window)
{
    for (auto& particle : particleSystem.existingParticles)
    {
        window.draw(particle.shape);
    }
}


void ParticulesManager::render()
{

}