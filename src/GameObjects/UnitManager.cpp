#include "GameObjects/UnitManager.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "GameObjects/Asteroid.h"
#define USE_MATH_DEFINES
#include <corecrt_math_defines.h>
#include "../../include/GameObjects/PoolManager.h"

void Asteroids::GameObjects::UnitManager::Start()
{
    Core::Events::EventSystem::GetInstance().RegisterEvent<SpawnUnitEvent>(Core::Events::EventType::GameEvent);
    Core::Events::EventSystem::GetInstance().SubscribeToEvent<SpawnUnitEvent>(Core::Events::EventType::GameEvent,
        [this](const std::any& event)
        {
           SpawnUnitEvent spawnEvent = std::any_cast<SpawnUnitEvent>(event);
           SpawnUnit(spawnEvent.m_unitType);
        });

    for (uint8_t i = 0; i < 5; i++)
    {
        SpawnUnit(UnitType::Asteroid);
    }
}

void Asteroids::GameObjects::UnitManager::SpawnUnit(UnitType someUnitType)
{
    static std::uniform_real_distribution<float> spawnPointDistribution(0.0f, 1.0f);
    float randomPointOnUnitCircle = spawnPointDistribution(m_randomGenerator) * 2 * M_PI;
    glm::vec2 spawnPosition = m_spawnCenter +
        glm::vec2(std::cos(randomPointOnUnitCircle),
                  std::sin(randomPointOnUnitCircle)) * (m_spawnCircleRadius);

    switch (someUnitType)
    {
    default:
    case UnitType::Asteroid:
        {
            Asteroid* asteroid = static_cast<Asteroid*>(PoolManager::GetInstance
                (GetSceneReference()).GetObjectFromPool<Asteroid>());
            asteroid->m_size = 75.0f;
            asteroid->m_startingPosition = spawnPosition;
            asteroid->m_activeRadius = m_spawnCircleRadius + 10.0f;
            asteroid->ResetVelocity();
            asteroid->m_isActive = true;
            break;
        }

    case UnitType::EnemyShip:
        {
            break;
        }
    }
}

void Asteroids::GameObjects::UnitManager::Update(const float deltaTime)
{
}
