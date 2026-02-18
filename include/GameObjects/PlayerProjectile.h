#pragma once
#include "ProjectileBase.h"
#include "GameObjects/ObjectPooling/ProjectileObjectPool.h"

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

    private:
        ProjectileObjectPool::ReturnProjectileToPoolEvent m_returnToPoolEvent = ProjectileObjectPool::ReturnProjectileToPoolEvent(this);
    };
}
