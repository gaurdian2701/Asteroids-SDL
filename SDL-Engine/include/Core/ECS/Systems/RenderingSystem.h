#pragma once
#include "Core/ECS/ECSManager.h"
#include "Assets/Components/Transform.h"
#include "System.h"
#include "Assets/Components/Renderer2D.h"


namespace Core::ECS::Systems
{
    class RenderingSystem : public System
    {
    public:
        RenderingSystem() = default;
        void BeginSystem() override;
        void UpdateSystem() override;
        void EndSystem() override;

    private:
        std::tuple<std::vector<Assets::Components::Transform>&,
        std::vector<Assets::Components::Renderer2D>&> m_interestedDenseComponentArrays =
            ECSManager::GetInstance().QueryDenseComponentArrays<Assets::Components::Transform,
            Assets::Components::Renderer2D>();

        std::tuple<std::vector<std::uint32_t>&, std::vector<std::uint32_t>&> m_interestedSparseArrays =
            ECSManager::GetInstance().QuerySparseEntityArrays<Assets::Components::Transform, Assets::Components::Renderer2D>();
    };
}
