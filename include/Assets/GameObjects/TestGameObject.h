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
		float m_moveSpeed = 10;
	};
}
