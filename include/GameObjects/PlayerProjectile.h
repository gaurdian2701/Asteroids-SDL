#pragma once
#include "PoolManager.h"
#include "ProjectileBase.h"

namespace Asteroids::GameObjects
{
    class PlayerProjectile : public ProjectileBase
    {
    public:
        PlayerProjectile() = default;
        ~PlayerProjectile() override = default;

        void AddComponentsBeforeStartup() override;
        void Start() override;
        void Update(const float deltaTime) override;
    };
}
