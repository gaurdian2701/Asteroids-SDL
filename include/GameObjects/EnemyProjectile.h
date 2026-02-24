#pragma once
#include "ProjectileBase.h"

namespace Asteroids::GameObjects
{
	class EnemySpaceship;
}

namespace Asteroids::GameObjects
{
	class PoolManager;
}

namespace Asteroids::GameObjects
{
	class SpaceShip;
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
		EnemySpaceship* m_shooter = nullptr;
		SpaceShip* m_player = nullptr;
		PoolManager* m_poolManager = nullptr;
	};
}
