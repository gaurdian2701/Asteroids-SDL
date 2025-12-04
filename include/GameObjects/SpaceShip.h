#pragma once
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"
#include "SDL3/SDL_render.h"

namespace Assets::GameObjects
{
	class SpaceShip : public Scene::GameObject
	{
	public:
		void Start() override;
		void Update(const float deltaTime) override;

	private:
		void UpdateAimPosition();
		void EvaluateMovementInput(const float deltaTime);

	private:
		float m_moveSpeed = 50.0f;
		float m_rotationSpeed = 10.0f;
		float m_aimAngle = 0.0f;
		float m_aimCircleRadius = 0.0f;

		glm::vec<2, int> m_movementVector = glm::vec<2, int>(0);
	};
}
