#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameActions
{
	class PlayerControlAction;
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
		void ShootBullet();

	private:
		float m_moveSpeed = 100.0f;
		float m_timePerShot = 0.3f;
		float m_shootTimer = 0.0f;
		float m_bulletLaunchOffset = 20.0f;
		Actions::ActionStack* m_spaceshipActionStack = nullptr;
		GameActions::PlayerControlAction* m_playerControlAction = nullptr;
	};
}
