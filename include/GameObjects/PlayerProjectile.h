#pragma once
#include "ProjectileBase.h"

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
    class PlayerProjectile : public ProjectileBase
    {
    public:
        PlayerProjectile() = default;
        ~PlayerProjectile() override = default;

        void Start() override;
        void DisableProjectile() override;
        void CheckForCollisions() override;

    private:
        Player* m_player = nullptr;
        PoolManager* m_poolManager = nullptr;
    };
}
