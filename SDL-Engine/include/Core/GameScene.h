#pragma once
#include "vec2.hpp"
#include "Application/Application.h"
#include "Core/ECS/ECSManager.h"
#include "PrintDebug.h"

namespace Scene
{
    class GameObject;
}

namespace Core
{
    class GameScene
    {
    public:
        explicit GameScene(const std::uint32_t maxEntitiesInScene);
        virtual ~GameScene() = default;

        virtual void CreateGameObjects() = 0;
        virtual void InitializeScene();

        virtual void Start();
        virtual void Update(const float deltaTime);

        ECS::ECSManager& GetECSManager();

        void DeleteGameObject(Scene::GameObject* someGameObject);
        inline void UnTrackGameObject(Scene::GameObject* someGameObject);
        void GarbageCollect();
        void CleanupScene();

#ifdef _DEBUG
        virtual void SetGameObjectDebugNames(){}
#endif

        bool IsGameObjectOutOfBounds(Scene::GameObject* someGameObject);

        template<typename T>
        void AddComponentToEntity(Scene::GameObject& someGameObject, const std::uint32_t someEntityID)
        {
            m_ECSManager.AddComponent<T>(someEntityID);
            AddComponentToGameObjectData(someGameObject,
                m_ECSManager.GetGeneratedComponentTypeIndex<T>(m_ECSManager));
        }

        template<typename T>
        void RemoveComponentFromEntity(Scene::GameObject& someGameObject, const std::uint32_t someEntityID)
        {
            m_ECSManager.RemoveComponent<T>(someEntityID);
            RemoveComponentFromGameObjectData(someGameObject,
                m_ECSManager.GetGeneratedComponentTypeIndex<T>(m_ECSManager));
        }

        void RemoveComponentFromEntityUsingTypeIndex(const std::uint32_t someEntityID,
            const std::size_t someComponentTypeIndex);

        void AddComponentToGameObjectData(Scene::GameObject& someGameObject, std::size_t someComponentTypeIndex);
        void RemoveComponentFromGameObjectData(Scene::GameObject& someGameObject, std::size_t someComponentTypeIndex);

        template<std::derived_from<Scene::GameObject> GameObjectType, typename ...Args>
        GameObjectType* AddGameObject(Args&&... gameObjectArguments)
        {
            if (m_gameObjectsInScene.size() == m_maxEntityCount)
            {
                PrintDebug("%s", "SCENE MAX ENTITY CAPACITY REACHED");
                return nullptr;
            }

            m_gameObjectsInScene.push_back(new GameObjectType(std::forward<Args>(gameObjectArguments)...));
            InitializeGameObject(m_gameObjectsInScene.back());
            return static_cast<GameObjectType*>(m_gameObjectsInScene.back());
        }

    protected:
        virtual void InitializeGameObjectReferences(){}
#ifdef _DEBUG
        virtual void UpdateImGuiDebugs();
#endif

    private:
        void InitializeGameObject(Scene::GameObject* someGameObject);
        void RegisterComponents();

    protected:
        std::vector<Scene::GameObject*> m_gameObjectsInScene;

    private:
        ECS::ECSManager m_ECSManager;
        std::vector<Scene::GameObject*> m_startQueue = std::vector<Scene::GameObject*>();
        uint32_t m_maxEntityCount = 0;
        glm::vec2 m_minCartesianLimits = glm::vec2(0.0f);
        glm::vec2 m_maxCartesianLimits = glm::vec2(0.0f);
    };
}
