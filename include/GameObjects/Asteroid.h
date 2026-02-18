#pragma once
#include "UnitManager.h"
#include "ObjectPooling/UnitObjectPool.h"
#include "ObjectPooling/UnitObjectPool.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class Asteroid : public Scene::GameObject
	{
	public:
		Asteroid() = default;
		~Asteroid() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void Update(const float deltaTime) override;
		void ResetVelocity();

	public:
		float m_size = 75.0f;
		float m_activeRadius = 0.0f;
		bool m_isActive = true;
		glm::vec2 m_startingPosition = glm::vec2(0.0f);

	private:
		float m_moveSpeed = 200.0f;
		float m_rotationSpeed = 3.0f;
		float m_velocityDirectionDeviation = 0.0f;
		std::default_random_engine m_randomGenerator;
		glm::vec2 m_initialVelocity = glm::vec2(0.0f);
        UnitObjectPool::ReturnUnitToPoolEvent m_returnToPoolEvent = UnitObjectPool::ReturnUnitToPoolEvent(this);
		UnitManager::SpawnUnitEvent m_spawnEvent = UnitManager::SpawnUnitEvent(UnitManager::UnitType::Asteroid);
	};
}
