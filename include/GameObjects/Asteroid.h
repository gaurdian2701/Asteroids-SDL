#pragma once
#include "IHostile.h"
#include "UnitManager.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class Asteroid : public Scene::GameObject, public IHostile
	{
	public:
		Asteroid() = default;
		~Asteroid() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void Update(const float deltaTime) override;
		void InitializeAsteroid(glm::vec2&& someStartingPosition,
			glm::vec2&& someMovementDirection,
			float someScale,
			float someAngularDeviationInDegrees,
			float someActiveRadius);

		void ResetVelocity();
		void OnHit() override;

	public:
		float m_startingScale = 75.0f;
		float m_activeRadius = 0.0f;
		float m_velocityAngularDeviationInDegrees = 20.0f;
		bool m_alreadySplit = false;
		glm::vec2 m_startingPosition = glm::vec2(0.0f);
		glm::vec2 m_movementDirection = glm::vec2(0.0f);

	private:
		float m_moveSpeed = 100.0f;
		float m_rotationSpeed = 3.0f;
		float m_particleSpeed = 100.0f;
		std::default_random_engine m_randomGenerator;
		UnitManager::UnitLeftActiveRadiusEvent m_onLeftActiveRadiusEvent =
				UnitManager::UnitLeftActiveRadiusEvent(this, UnitManager::UnitType::Asteroid);
		UnitManager::UnitDestroyedEvent m_onDestroyedEvent =
			UnitManager::UnitDestroyedEvent(this, UnitManager::UnitType::Asteroid);
	};
}
