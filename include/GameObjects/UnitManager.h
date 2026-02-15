#pragma once
#include <random>
#include "Scene/GameObject.h"

namespace Actions
{
	class ActionStack;
}

namespace Asteroids::GameObjects
{
	class UnitManager : public Scene::GameObject
	{
		enum class UnitType : uint8_t
		{
			Asteroid = 0,
			EnemyShip = 1
		};

		class SpawnUnitEvent
		{
			UnitType m_unitType = UnitType::Asteroid;
			float m_unitSize = 50.0f;
		};

	public:
		UnitManager() = default;
		~UnitManager() override = default;

		void Start() override;
		void Update(const float deltaTime) override;

	private:
		void SpawnUnit(UnitType someUnitType, float someUnitSize);

	private:
		float m_defaultAsteroidSize = 75.0f;
		float m_spawnCircleRadius = 300.0f;
		uint8_t m_maxDeviationForUnitHomingDirection = 50;
		std::vector<GameObject*> m_managedUnits = std::vector<GameObject*>();
		std::default_random_engine m_randomGenerator;
		const glm::vec2 m_spawnCenter = glm::vec2(0.0f);
	};
}
