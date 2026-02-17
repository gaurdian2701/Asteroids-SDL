#include "GameObjects/UnitManager.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "GameObjects/Asteroid.h"
#define USE_MATH_DEFINES
#include <corecrt_math_defines.h>
#include <string>

void Asteroids::GameObjects::UnitManager::Start()
{
	Core::Events::EventSystem::GetInstance().RegisterEvent<SpawnUnitEvent>(Core::Events::EventType::GameEvent);

	for (uint8_t i = 0; i < 5; i++)
	{
		SpawnUnit(UnitType::Asteroid, 75.0f);
	}
}

void Asteroids::GameObjects::UnitManager::SpawnUnit(UnitType someUnitType, float someUnitSize)
{
	static std::uniform_real_distribution<float> spawnPointDistribution(0.0f, 1.0f);
	float randomPointOnUnitCircle = spawnPointDistribution(m_randomGenerator) * 2 * M_PI;
	glm::vec2 spawnPosition = m_spawnCenter +
		glm::vec2(std::cos(randomPointOnUnitCircle),
			std::sin(randomPointOnUnitCircle)) * m_spawnCircleRadius;

	switch (someUnitType)
	{
		default:
		case UnitType::Asteroid:
		{
			Asteroid* asteroid = GetSceneReference().AddGameObject<Asteroid>();
			asteroid->m_size = someUnitSize;
			asteroid->m_startingPosition = spawnPosition;
			m_managedUnits.push_back(asteroid);
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



