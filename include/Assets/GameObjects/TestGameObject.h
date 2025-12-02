#pragma once
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"

namespace Assets::GameObjects
{
	class TestGameObject : public Scene::GameObject
	{
	public:
		void Start() override;
		void Update(const float deltaTime) override;

	private:
		void EvaluateMovementInput();

	private:
		float m_moveSpeed = 50;
		glm::vec<2, int> m_movementVector = glm::vec<2, int>(0);
	};
}
