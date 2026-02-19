#pragma once
#include <random>
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

		struct SpawnUnitEvent
		{
			explicit SpawnUnitEvent(UnitType someUnitType) : m_unitType(someUnitType) {}
			UnitType m_unitType = UnitType::Asteroid;
		};

		UnitManager() = default;
		~UnitManager() override = default;

		void Start() override;
		void Update(const float deltaTime) override;

	private:
		void SpawnUnit(UnitType someUnitType);

	private:
		float m_defaultAsteroidSize = 75.0f;
		float m_spawnCircleRadius = 650.0f;
		std::default_random_engine m_randomGenerator;
		const glm::vec2 m_spawnCenter = glm::vec2(0.0f);
	};
}
