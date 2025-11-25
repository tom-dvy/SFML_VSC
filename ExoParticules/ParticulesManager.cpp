#include "ParticulesManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.h"
#include <windows.h>
#include<random>

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
        newParticle.timeToLive = particleSystem->minLifeTime +
                                 (particleSystem->maxLifeTime - particleSystem->minLifeTime) * ((float)rand() / RAND_MAX);

        particleSystem->existingParticles.push_back(newParticle);
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

void ParticulesManager::PlayParticleSystem(sParticleSystem* particleSystem)
{
    particleSystem->isPlaying = true;
    particleSystem->elapsedSystemTime = 0.f;
}

bool ParticulesManager::IsParticleSystemPlaying(sParticleSystem* particleSystem)
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
        sParticleSystem launcher = CreateParticleSystem(
            1.0f, 0.0f, 0.0f,
            sf::Vector2f(x, 580.0f),
            0.0f,
            3.0f
        );

        launcher.systemLifeTime = 2.0f;
        launcher.isPlaying = true;
        launcher.hasExploded = false;
        launcher.frictionCoef = 0.2f;

        sParticle rocket;
        rocket.timeToLive = launcher.systemLifeTime;
        rocket.moveSpeed = 700;
        rocket.direction = sf::Vector2f(0, -1);
        rocket.shape.setRadius(3);
        rocket.shape.setOrigin(3, 3);
        rocket.shape.setPosition(x, 580);
        rocket.shape.setFillColor(sf::Color::White);

        launcher.existingParticles.push_back(rocket);

        fireworkSystems.push_back(launcher);
    }

    for (size_t i = 0; i < fireworkSystems.size(); ++i)
    {
        auto& sys = fireworkSystems[i];
        UpdateParticleSystem(&sys, deltaTime);

        if (!sys.isPlaying && !sys.hasExploded)
        {
            sf::Vector2f pos = sys.origin;

            sParticleSystem explosion = CreateParticleSystem(
                0.02f,
                0.8f,
                1.6f,
                pos,
                0.0f,
                3.0f
            );

            explosion.systemLifeTime = 0.35f;
            explosion.isPlaying = true;
            explosion.hasExploded = true;

            const int count = 40 + rand() % 40;
            const float PI = 3.14159265f;

            for (int j = 0; j < count; ++j)
            {
                sParticle p;
                p.timeToLive = explosion.minLifeTime +
                    (explosion.maxLifeTime - explosion.minLifeTime) * ((float)rand() / RAND_MAX);

                float angle = PI * 2.0f * ((float)rand() / RAND_MAX);
                p.direction = sf::Vector2f(cos(angle), sin(angle));
                p.moveSpeed = 80 + rand() % 300;

                float size = explosion.particleSize * (0.5f + ((float)rand() / RAND_MAX));
                p.shape.setRadius(size);
                p.shape.setOrigin(size, size);
                p.shape.setPosition(pos);

                p.shape.setFillColor(sf::Color(
                    120 + rand() % 136,
                    120 + rand() % 136,
                    120 + rand() % 136
                ));

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
            [](const sParticleSystem& s) {
                return (!s.isPlaying && s.existingParticles.empty());
            }
        ),
        fireworkSystems.end()
    );
}

void ParticulesManager::DrawFireworks(sf::RenderWindow& window)
{
    for (auto& sys : fireworkSystems)
    {
        DrawParticleSystem(sys, window);
    }
}
