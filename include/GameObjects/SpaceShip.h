#pragma once
#include "Actions/ActionStack.h"
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class PoolManager;
}

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
		~SpaceShip() override
		{
			m_projectileTexture = nullptr;
			m_controlAction = nullptr;
			m_actionStack->End();
			delete m_actionStack;
		}

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void Update(float deltaTime) override;
		void OnHit();

	private:
		void DoShooting();
		void WrapPosition();

	private:
		float m_timePerShot = 0.5f;
		float m_shootTimer = 0.0f;
		float m_bulletLaunchOffset = 20.0f;
		glm::vec2 m_maxCartesianLimits = glm::vec2(0.0f);
		glm::vec2 m_minCartesianLimits = glm::vec2(0.0f);
		SDL_Texture* m_projectileTexture = nullptr;
		Assets::Components::Transform* m_transform = nullptr;
		Actions::ActionStack* m_actionStack = nullptr;
		GameActions::PlayerControlAction* m_controlAction = nullptr;
		PoolManager* m_poolManager = nullptr;
	};
}
