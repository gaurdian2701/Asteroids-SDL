#pragma once
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"

namespace Assets::GameObjects
{
	class SpaceShip : public Scene::GameObject
	{
	public:
		void Start() override;
		void Update(float deltaTime) override;

	private:
		void UpdateAimPosition();
		void EvaluateMovementInput(float deltaTime);

	private:
		float m_moveSpeed = 100.0f;
		float m_rotationSpeed = 100.0f;
		float m_rotationAngle = 0.0f;
		float m_aimCircleRadius = 0.0f;

		glm::vec<2, int> m_movementVector = glm::vec<2, int>(0);
	};
}
