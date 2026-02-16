#pragma once
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

	public:
		float m_size = 75.0f;
		glm::vec2 m_startingPosition = glm::vec2(0.0f);

	private:
		bool m_hasRenderer = true;
		float m_timeToToggleComponent = 1.0f;
		float m_timer = 0.0f;
		float m_moveSpeed = 75.0f;
		float m_rotationSpeed = 3.0f;
		float m_velocityDirectionDeviation = 0.0f;
		std::default_random_engine m_randomGenerator;
		glm::vec2 m_initialVelocity = glm::vec2(0.0f);
	};
}
