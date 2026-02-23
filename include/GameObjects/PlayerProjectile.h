#pragma once
#include "ProjectileBase.h"

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
    class PlayerProjectile : public ProjectileBase
    {
    public:
        PlayerProjectile() = default;
        ~PlayerProjectile() override = default;

        void Start() override;
        void DisableProjectile() override;
        void CheckForCollisions() override;

    private:
        SpaceShip* m_player = nullptr;
        PoolManager* m_poolManager = nullptr;
    };
}
