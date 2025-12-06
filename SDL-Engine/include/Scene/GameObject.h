#pragma once
#include <cstdint>
#include "Core/GameScene.h"

namespace Scene
{
    class GameObject
    {
    public:
        //Making a default constructor grants some flexibility to create objects not tracked by the scene as well
        GameObject() = default;

        virtual ~GameObject()
        {
            for (std::size_t typeIndex = 0; typeIndex < Core::ECS::MAX_COMPONENT_TYPES; typeIndex++)
            {
                if (m_componentBitSet[typeIndex])
                {
                    m_sceneReference->RemoveComponentFromEntityUsingTypeIndex(m_entityID, typeIndex);
                }
            }

            m_sceneReference->UnTrackGameObject(this);
            m_sceneReference = nullptr;
            
            //TODO: YOU DO NOT REMOVE COMPONENTS HERE.
            //TODO: YOU HAVE TO INCLUDE FUNCTIONALITY TO REMOVE COMPONENTS ASSOCIATED WITH THIS GAMEOBJECT.
            //TODO: MAYBE STORE A BITSET SOMEWHERE TO CALL THE RESPECTIVE REMOVE COMPONENT FUNCTIONS.
        }

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

    private:
        std::uint32_t m_entityID = Core::INVALID_INDEX;
        Core::GameScene* m_sceneReference = nullptr;
        std::bitset<Core::ECS::MAX_COMPONENT_TYPES> m_componentBitSet;

        friend class Core::GameScene;
    };
}
