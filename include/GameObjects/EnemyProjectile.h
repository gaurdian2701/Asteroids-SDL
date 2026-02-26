#pragma once
#include "ProjectileBase.h"

namespace Asteroids::GameObjects
{
	class Enemyship;
}

namespace Asteroids::GameObjects
{
	class PoolManager;
}

namespace Asteroids::GameObjects
{
	class Player;
}

namespace Asteroids::GameObjects
{
	class EnemyProjectile : public ProjectileBase
	{
	public:
		EnemyProjectile() = default;
		~EnemyProjectile() override = default;

		void Start() override;
		void DisableProjectile() override;
		void CheckForCollisions() override;

	private:
		Enemyship* m_shooter = nullptr;
		Player* m_player = nullptr;
		PoolManager* m_poolManager = nullptr;
	};
}
