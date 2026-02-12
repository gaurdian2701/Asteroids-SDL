#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameActions
{
	class PlayerInputAction;
}

namespace Actions
{
	class ActionStack;
}

namespace Asteroids::GameObjects
{
	class SpaceShip : public Scene::GameObject
	{
	public:
		SpaceShip() = default;
		~SpaceShip() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void Update(float deltaTime) override;

	private:
		float m_moveSpeed = 100.0f;
		Actions::ActionStack* m_spaceshipActionStack = nullptr;
	};
}
