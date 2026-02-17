#pragma once
#include "IProjectile.h"

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
    };
}
