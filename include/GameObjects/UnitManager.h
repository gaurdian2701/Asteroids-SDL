#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class PoolManager;
}

namespace Actions
{
	class ActionStack;
}

namespace Asteroids::GameObjects
{
	class UnitManager : public Scene::GameObject
	{
	public:
		enum class UnitType : uint8_t
		{
			Asteroid = 0,
			EnemyShip = 1
		};

		struct UnitLeftActiveRadiusEvent
		{
			explicit UnitLeftActiveRadiusEvent(GameObject* someUnit, UnitType someUnitType) :
			Unit(someUnit), UnitType(someUnitType) {}

			GameObject* Unit = nullptr;
			UnitType UnitType = UnitType::Asteroid;
		};

		struct UnitDestroyedEvent
		{
			explicit UnitDestroyedEvent(GameObject* someUnit, UnitType someUnitType) :
			Unit(someUnit), UnitType(someUnitType) {}

			GameObject* Unit = nullptr;
			UnitType UnitType = UnitType::Asteroid;
		};

		UnitManager() = default;
		~UnitManager() override = default;

		void Start() override;
		void Update(const float deltaTime) override;
		void End() override;

	private:
		void SpawnUnit(UnitType someUnitType);
		void OnUnitLeftActiveRadius(GameObject* someUnit, UnitType someUnitType);
		void OnUnitDestroyed(GameObject* someUnit, UnitType someUnitType);

	private:
		float m_timeBetweenAsteroidSpawns = 3.0f;
		float m_timeBetweenEnemySpawns = 10.0f;
		float m_asteroidSpawnTimer = 0.0f;
		float m_enemySpawnTimer = 0.0f;
		float m_timeTillFirstEnemySpawn = 20.0f;
		float m_defaultAsteroidSize = 75.0f;
		float m_spawnCircleRadius = 650.0f;
		uint32_t m_leftActiveRadiusFunctionID = 0;
		uint32_t m_unitDestroyedFunctionID = 0;
		const glm::vec2 m_spawnCenter = glm::vec2(0.0f);
		PoolManager* m_poolManager = nullptr;
	};
}
