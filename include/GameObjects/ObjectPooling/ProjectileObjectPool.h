#pragma once
#include "GenericObjectPool.h"

namespace Asteroids::GameObjects
{
    class ProjectileBase;

    class ProjectileObjectPool : public GenericObjectPool
    {
    public:
        ProjectileObjectPool(uint32_t maxPoolSize) : GenericObjectPool(maxPoolSize){}
        ~ProjectileObjectPool() override = default;
        void Start() override;

        struct ReturnProjectileToPoolEvent
        {
            explicit ReturnProjectileToPoolEvent(ProjectileBase* someProjectile) : m_someProjectile(someProjectile) {}
            ProjectileBase* m_someProjectile = nullptr;
        };
    };
}
