#pragma once
#include <cstdint>
#include "Core/GameScene.h"

namespace Core
{
    class GameScene;
}

namespace Scene
{
    class GameObject
    {
    public:
        //Making a default constructor grants some flexibility to create objects not tracked by the scene as well
        GameObject() = default;

        virtual ~GameObject()
        {
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
            m_sceneReference->GetECSManager().AddComponent<T>(m_entityID);
        }

        template<typename T>
        void RemoveComponent()
        {
            m_sceneReference->GetECSManager().RemoveComponent<T>(m_entityID);
        }

        template<typename T>
        T& GetComponent()
        {
            return m_sceneReference->GetECSManager().GetComponent<T>(m_entityID);
        }

    private:
        std::uint32_t m_entityID = -1;
        Core::GameScene* m_sceneReference = nullptr;

        friend class Core::GameScene;
    };
}
