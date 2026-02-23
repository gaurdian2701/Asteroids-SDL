#include "GameObjects/UnitManager.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "GameObjects/Asteroid.h"
#define USE_MATH_DEFINES
#include "GameObjects/PoolManager.h"
#include "Assets/Components/Transform.h"
#include <gtx/rotate_vector.hpp>
#include "MiscFunctions.h"
#include "GameObjects/EnemySpaceship.h"

void Asteroids::GameObjects::UnitManager::Start()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	Core::Events::EventSystem::GetInstance().RegisterEvent<UnitLeftActiveRadiusEvent>(Core::Events::EventType::GameEvent);
	Core::Events::EventSystem::GetInstance().RegisterEvent<UnitDestroyedEvent>(Core::Events::EventType::GameEvent);

	m_leftActiveRadiusFunctionID = Core::Events::EventSystem::GetInstance().SubscribeToEvent<UnitLeftActiveRadiusEvent>(
		Core::Events::EventType::GameEvent,
		[this](const std::any &event)
		{
			UnitLeftActiveRadiusEvent leftRadiusEvent = std::any_cast<UnitLeftActiveRadiusEvent>(event);
			OnUnitLeftActiveRadius(leftRadiusEvent.Unit, leftRadiusEvent.UnitType);
		});

	m_unitDestroyedFunctionID = Core::Events::EventSystem::GetInstance().SubscribeToEvent<UnitDestroyedEvent>(Core::Events::EventType::GameEvent,
		[this](const std::any &event)
		{
			UnitDestroyedEvent destroyedEvent = std::any_cast<UnitDestroyedEvent>(event);
			OnUnitDestroyed(destroyedEvent.Unit, destroyedEvent.UnitType);
		});

	m_poolManager = GetSceneReference().GetGameObjectUsingType<PoolManager>();
	
	m_poolManager->RegisterPoolMap<Asteroid>();
	m_poolManager->RegisterPoolMap<EnemySpaceship>();

	for (uint8_t i = 0; i < 5; i++) {
		SpawnUnit(UnitType::Asteroid);
	}
}

void Asteroids::GameObjects::UnitManager::SpawnUnit(UnitType someUnitType)
{
	glm::vec2 spawnPosition = MiscFunctions::GetRandomPointOnCircle(glm::vec2(0.0f), m_spawnCircleRadius);

	switch (someUnitType)
	{
		default:
		case UnitType::Asteroid:
		{
			Asteroid *asteroid = m_poolManager->GetObjectFromPool<Asteroid>();

			if (asteroid != nullptr)
			{
				asteroid->InitializeAsteroid(std::forward<glm::vec2>(spawnPosition),
				                             -glm::normalize(spawnPosition),
				                             75.0f, 20.0f, m_spawnCircleRadius + 10.0f);
				asteroid->ResetVelocity();
				asteroid->m_isActive = true;
				asteroid->m_alreadySplit = false;
			}
			break;
		}

		case UnitType::EnemyShip:
		{
			EnemySpaceship* enemyShip = m_poolManager->GetObjectFromPool<EnemySpaceship>();

			if (enemyShip != nullptr)
			{
				enemyShip->GetComponent<Assets::Components::Transform>()->LocalPosition = spawnPosition;
				enemyShip->m_isActive = true;
			}
			break;
		}
	}
}

void Asteroids::GameObjects::UnitManager::Update(const float deltaTime)
{
	//Spawn Asteroids
	if (m_asteroidSpawnTimer > m_timeBetweenAsteroidSpawns)
	{
		m_asteroidSpawnTimer = 0.0f;
		for (uint8_t i = 0; i < 3; i++)
		{
			SpawnUnit(UnitType::Asteroid);
		}
	}
	m_asteroidSpawnTimer += deltaTime;

	//Spawn enemies
	if (m_enemySpawnTimer > m_timeTillFirstEnemySpawn)
	{
		m_timeTillFirstEnemySpawn = 0.0f;

		if (m_enemySpawnTimer > m_timeBetweenEnemySpawns)
		{
			m_enemySpawnTimer = 0.0f;
			SpawnUnit(UnitType::EnemyShip);
		}
	}
	m_enemySpawnTimer += deltaTime;
}

void Asteroids::GameObjects::UnitManager::End()
{
	Core::Events::EventSystem::GetInstance().UnsubscribeFromEvent<UnitLeftActiveRadiusEvent>(Core::Events::EventType::GameEvent, m_leftActiveRadiusFunctionID);
	Core::Events::EventSystem::GetInstance().UnsubscribeFromEvent<UnitDestroyedEvent>(Core::Events::EventType::GameEvent, m_unitDestroyedFunctionID);

	Core::Events::EventSystem::GetInstance().UnRegisterEvent<UnitLeftActiveRadiusEvent>(Core::Events::EventType::GameEvent);
	Core::Events::EventSystem::GetInstance().UnRegisterEvent<UnitDestroyedEvent>(Core::Events::EventType::GameEvent);
}

void Asteroids::GameObjects::UnitManager::OnUnitLeftActiveRadius(GameObject *someUnit, UnitType someUnitType)
{
	if (someUnit != nullptr) {
		someUnit->m_isActive = false;

		switch (someUnitType)
		{
			case UnitType::Asteroid:
			{
				Asteroid *asteroid = static_cast<Asteroid*>(someUnit);
				if (asteroid != nullptr) {
					m_poolManager->ReturnObjectToPool<Asteroid>(asteroid);
				}
				break;
			}

			default:
			case UnitType::EnemyShip:
				break;
		}
	}
}

void Asteroids::GameObjects::UnitManager::OnUnitDestroyed(GameObject *someUnit, UnitType someUnitType)
{
	if (someUnit != nullptr)
	{
		someUnit->m_isActive = false;
		glm::vec2 respawnPoint = MiscFunctions::GetRandomPointOnCircle(glm::vec2(0.0f), m_spawnCircleRadius);

		switch (someUnitType)
		{
			case UnitType::Asteroid:
			{
				Asteroid *asteroid = static_cast<Asteroid *>(someUnit);
				float halfSize = asteroid->m_startingScale * 0.5f;
				if (asteroid != nullptr)
				{
					auto asteroidTransform = asteroid->GetComponent<Assets::Components::Transform>();

					if (!asteroid->m_alreadySplit) {
						//Spawn smaller asteroids
						Asteroid *firstAsteroid = static_cast<Asteroid *>
								(m_poolManager->GetObjectFromPool<Asteroid>());
						Asteroid *secondAsteroid = static_cast<Asteroid *>
								(m_poolManager->GetObjectFromPool<Asteroid>());

						if (firstAsteroid && secondAsteroid)
						{
							firstAsteroid->m_isActive = true;
							secondAsteroid->m_isActive = true;
							firstAsteroid->m_alreadySplit = true;
							secondAsteroid->m_alreadySplit = true;

							//Initialize values and make them split 45 in each direction
							firstAsteroid->InitializeAsteroid(std::forward<glm::vec2>(asteroidTransform->LocalPosition),
															  glm::rotate(asteroid->m_movementDirection,
																		  glm::radians(45.0f)),
															  halfSize, 0.0f, m_spawnCircleRadius + 10.0f);
							secondAsteroid->InitializeAsteroid(std::forward<glm::vec2>(asteroidTransform->LocalPosition),
															   glm::rotate(asteroid->m_movementDirection,
																		   glm::radians(-45.0f)),
															   halfSize, 0.0f, m_spawnCircleRadius + 10.0f);

							firstAsteroid->ResetVelocity();
							secondAsteroid->ResetVelocity();
						}
					}

					asteroidTransform->LocalPosition = respawnPoint;
					m_poolManager->ReturnObjectToPool<Asteroid>(asteroid);
				}
				break;
			}

			case UnitType::EnemyShip:
				EnemySpaceship *enemy = static_cast<EnemySpaceship*>(someUnit);
				if (enemy != nullptr)
				{
					enemy->GetComponent<Assets::Components::Transform>()->LocalPosition = respawnPoint;
				}
				break;
		}
	}
}
