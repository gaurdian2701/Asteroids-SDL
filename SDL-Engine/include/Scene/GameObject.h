#pragma once
#include <cstdint>
#include "Core/GameScene.h"
#include "glm.hpp"

namespace Scene
{
    class GameObject
    {
    public:
        //Making a default constructor grants some flexibility to create objects not tracked by the scene as well
        GameObject() = default;
        virtual ~GameObject() = default;

        virtual void AddComponentsBeforeStartup(){}

        virtual void Start(){}

        virtual void Update(const float deltaTime){}
        [[nodiscard]] std::uint32_t GetEntityID() const { return m_entityID;}

        template<typename T>
        void AddComponent()
        {
            m_sceneReference->AddComponentToEntity<T>(*this, m_entityID);
        }

        template<typename T>
        void RemoveComponent()
        {
            m_sceneReference->RemoveComponentFromEntity<T>(*this, m_entityID);
        }

        template<typename T>
        T& GetComponent()
        {
            return m_sceneReference->GetECSManager().GetComponent<T>(m_entityID);
        }

    public:
#ifdef _DEBUG
        std::string m_name = "GameObject";
#endif
        GameObject* m_parent = nullptr;

    private:
        std::uint32_t m_entityID = Core::INVALID_ENTITY_ID;
        Core::GameScene* m_sceneReference = nullptr;
        std::bitset<Core::ECS::MAX_COMPONENT_TYPES> m_componentBitSet;

        friend class Core::GameScene;
    };
}
