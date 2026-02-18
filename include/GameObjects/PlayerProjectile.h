#pragma once
#include "IProjectile.h"
#include "ProjectilePool.h"

namespace Asteroids::GameObjects
{
    class PlayerProjectile : public IProjectile
    {
    public:
        PlayerProjectile() = default;
        ~PlayerProjectile() override = default;

        void AddComponentsBeforeStartup() override;
        void Start() override;
        void Update(const float deltaTime) override;

    private:
        ProjectilePool::ReturnProjectileToPoolEvent m_poolReturnEvent = ProjectilePool::ReturnProjectileToPoolEvent(this);
    };
}
