#include "ParticulesManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.h"
#include <windows.h>
#include <random>

ParticulesManager::ParticulesManager()
{
}

void ParticulesManager::AddParticleToSystem(sParticleSystem *particleSystem, float timeToLive)
{
    const float PI = 3.14159265f;

    sParticle newParticle;

    newParticle.timeToLive = timeToLive;
    newParticle.elapsedTime = 0;

    float angle = PI * 2.0f * (float)rand() / RAND_MAX;
    float distance = particleSystem->spawnRadius * sqrt((float)rand() / RAND_MAX);

    float x = particleSystem->origin.x + cos(angle) * distance;
    float y = particleSystem->origin.y + sin(angle) * distance;

    newParticle.moveSpeed = 100.0f;
    newParticle.direction = sf::Vector2f(cos(angle), sin(angle));

    float size = particleSystem->particleSize * ((float)rand() / RAND_MAX);
    std::cout << "Taille random des particules : " << size << std::endl;

    newParticle.shape.setRadius(size);
    newParticle.shape.setOrigin(size, size);
    newParticle.shape.setPosition(x, y);
    newParticle.shape.setFillColor(sf::Color::White);

    particleSystem->existingParticles.push_back(newParticle);
}

void ParticulesManager::UpdateParticleSystem(sParticleSystem *particleSystem, float deltaTime)
{
    if (!particleSystem->isPlaying)
        return;

    particleSystem->elapsedSystemTime += deltaTime;

    if (particleSystem->systemLifeTime > 0 &&
        particleSystem->elapsedSystemTime >= particleSystem->systemLifeTime)
    {
        particleSystem->isPlaying = false;
        return;
    }

    std::list<sParticle>::iterator it = particleSystem->existingParticles.begin();
    while (it != particleSystem->existingParticles.end())
    {
        sParticle &particule = *it;
        particule.elapsedTime += deltaTime;

        const float PI = 3.14159265f;
        float t = particule.elapsedTime;
        float maxT = particule.timeToLive;

        float scale = sin(PI * t / maxT);
        if (scale < 0.0f)
            scale = 1.0f;

        particule.shape.setScale(scale, scale);

        sf::Vector2f position = particule.shape.getPosition();
        position += particule.direction * particule.moveSpeed * deltaTime;
        particule.shape.setPosition(position);

        particule.moveSpeed = std::max(0.0f, particule.moveSpeed - particule.moveSpeed * particule.moveSpeed * particleSystem->frictionCoef * deltaTime);

        if (particule.elapsedTime >= particule.timeToLive)
        {
            particleSystem->origin = particule.shape.getPosition();

            it = particleSystem->existingParticles.erase(it);
            continue;
        }

        ++it;
    }

    particleSystem->chronoCreation += deltaTime;

    while (particleSystem->chronoCreation > particleSystem->creationPeriod)
    {
        particleSystem->chronoCreation -= particleSystem->creationPeriod;

        sParticle newParticle;
        newParticle.timeToLive = particleSystem->minLifeTime + (particleSystem->maxLifeTime - particleSystem->minLifeTime) * ((float)rand() / RAND_MAX);
        newParticle.moveSpeed = 100.0f;
        newParticle.direction = sf::Vector2f(0, -1);
        float size = particleSystem->particleSize * ((float)rand() / RAND_MAX);
        newParticle.shape.setRadius(size);
        newParticle.shape.setOrigin(size, size);
        newParticle.shape.setPosition(particleSystem->origin);
        newParticle.shape.setFillColor(sf::Color::White);

        particleSystem->existingParticles.push_back(newParticle);

    }

    if (particleSystem->existingParticles.empty())
    {
        particleSystem->isPlaying = false;
    }
}

void ParticulesManager::ClearParticleSystem(sParticleSystem *particleSystem)
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

void ParticulesManager::DrawParticleSystem(sParticleSystem &particleSystem, sf::RenderWindow &window)
{
    for (auto &particle : particleSystem.existingParticles)
    {
        window.draw(particle.shape);
    }
}

void ParticulesManager::PlayParticleSystem(sParticleSystem *particleSystem)
{
    particleSystem->isPlaying = true;
    particleSystem->elapsedSystemTime = 0.0f;
}

bool ParticulesManager::IsParticleSystemPlaying(sParticleSystem *particleSystem)
{
    return particleSystem->isPlaying;
}

void ParticulesManager::UpdateFireworks(float deltaTime)
{
    fireworkSpawnTimer += deltaTime;

    if (fireworkSpawnTimer >= nextFireworkSpawn)
    {
        fireworkSpawnTimer = 0;

        nextFireworkSpawn = 0.5f + ((float)rand() / RAND_MAX) * 1.0f;

        float x = 100 + rand() % 600;
        float yStart = 580;

        float minHeight = 200.0f;
        float maxHeight = 350.0f;
        float targetHeight = minHeight + ((float)rand() / RAND_MAX) * (maxHeight - minHeight);

        float systemLifeTime = 1.8f + ((float)rand() / RAND_MAX) * 0.7f; // 1.8 à 2.5 sec

        sParticleSystem launcher = CreateParticleSystem(
            1.0f, 0.0f, 0.0f,
            sf::Vector2f(x, yStart),
            0.0f,
            3.0f);

        launcher.systemLifeTime = systemLifeTime;
        launcher.isPlaying = true;
        launcher.hasExploded = false;
        launcher.frictionCoef = 0.0f;

        sParticle rocket;
        rocket.timeToLive = launcher.systemLifeTime;
        rocket.direction = sf::Vector2f(0, -1);
        rocket.moveSpeed = (yStart - targetHeight) / systemLifeTime;
        rocket.shape.setRadius(3);
        rocket.shape.setOrigin(3, 3);
        rocket.shape.setPosition(x, yStart);
        rocket.shape.setFillColor(sf::Color::White);

        launcher.existingParticles.push_back(rocket);
        fireworkSystems.push_back(launcher);
    }

    for (size_t i = 0; i < fireworkSystems.size(); ++i)
    {
        auto &sys = fireworkSystems[i];
        UpdateParticleSystem(&sys, deltaTime);

        if (!sys.isPlaying && !sys.hasExploded)
        {
            sf::Vector2f pos = sys.origin;
            if (!sys.existingParticles.empty())
            {
                pos = sys.existingParticles.front().shape.getPosition();
            }
            else
            {
                pos = sys.origin;
            }

            sParticleSystem explosion = CreateParticleSystem(0.02f, 0.8f, 1.6f, pos, 0.0f, 3.0f);

            explosion.systemLifeTime = 0.35f;
            explosion.isPlaying = true;
            explosion.hasExploded = true;

            const int count = 100 + rand() % 50;
            const float PI = 3.14159265f;

            for (int j = 0; j < count; ++j)
            {
                sParticle p;
                p.timeToLive = explosion.minLifeTime +
                               (explosion.maxLifeTime - explosion.minLifeTime) * ((float)rand() / RAND_MAX);

                float angle = PI * 2.0f * ((float)rand() / RAND_MAX);
                p.direction = sf::Vector2f(cos(angle), sin(angle));
                p.moveSpeed = 150 + rand() % 400;

                float size = explosion.particleSize * (1.0f + ((float)rand() / RAND_MAX) * 1.5F);
                p.shape.setRadius(size);
                p.shape.setOrigin(size, size);
                p.shape.setPosition(pos);
                p.shape.setFillColor(sf::Color(
                    120 + rand() % 136,
                    120 + rand() % 136,
                    120 + rand() % 136));

                explosion.existingParticles.push_back(p);
            }

            fireworkSystems.push_back(explosion);
            sys.hasExploded = true;
        }
    }

    fireworkSystems.erase(
        std::remove_if(
            fireworkSystems.begin(),
            fireworkSystems.end(),
            [](const sParticleSystem &s)
            {
                return (!s.isPlaying && s.existingParticles.empty());
            }),
        fireworkSystems.end());
}

void ParticulesManager::DrawFireworks(sf::RenderWindow &window)
{
    for (auto &sys : fireworkSystems)
    {
        DrawParticleSystem(sys, window);
    }
}
