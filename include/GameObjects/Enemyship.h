#pragma once
#include "IHostile.h"
#include "UnitManager.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class PoolManager;
}

namespace Assets::Components
{
	struct Transform;
}

namespace Asteroids::GameObjects
{
	class Player;
}

namespace Actions
{
	class ActionStack;
}

namespace Asteroids::GameObjects
{
	class Enemyship : public Scene::GameObject, public IHostile
	{
	public:
		Enemyship() = default;
		~Enemyship() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void Update(float deltaTime) override;
		void DoShooting();
		void OnHit() override;

	private:
		float m_timePerShot = 2.0f;
		float m_shootTimer = 0.0f;
		float m_bulletLaunchOffset = 20.0f;
		float m_minShootingDistance = 100.0f;
		float m_scale = 50.0f;

		glm::vec2 m_startingPosition = glm::vec2(0, 0);
		Actions::ActionStack* m_actionStack = nullptr;
		Player* m_player = nullptr;
		Assets::Components::Transform* m_transform = nullptr;
		SDL_Texture* m_projectileTexture = nullptr;
		PoolManager* m_poolManager = nullptr;
		UnitManager::UnitDestroyedEvent m_destroyedEvent =
			UnitManager::UnitDestroyedEvent(this, UnitManager::UnitType::EnemyShip);
	};
}
