#pragma once
#include "System.h"


namespace Core::ECS::Systems
{
    class RenderingSystem : public System
    {
    public:
        RenderingSystem() = default;
        void BeginSystem() override;
        void UpdateSystem(const float deltaTime) override;
        void EndSystem() override;
    };
}
