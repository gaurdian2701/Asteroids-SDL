#pragma once
#include "vec2.hpp"
#include "Application/Application.h"
#include "Core/ECS/ECSManager.h"

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

        virtual void InitializeGameObjects();
        void Start();
        virtual void Update(const float deltaTime);

        ECS::ECSManager& GetECSManager();

        static inline const glm::vec2& GetMaxCartesianLimits()
        {
            static glm::vec2 limits = glm::vec2(Application::SCREEN_WIDTH - Application::SCREEN_WIDTH/2,
                -Application::SCREEN_HEIGHT + Application::SCREEN_HEIGHT/2);
            return limits;
        }

        static inline const glm::vec2& GetMinCartesianLimits()
        {
            static glm::vec2 limits = glm::vec2(-Application::SCREEN_WIDTH/2,Application::SCREEN_HEIGHT/2);
            return limits;
        }


        template<typename T>
        void AddComponentToEntity(Scene::GameObject& someGameObject, const std::uint32_t someEntityID)
        {
            m_ECSManager.AddComponent<T>(someEntityID);
            AddComponentToGameObjectData(someGameObject,
                m_ECSManager.GetComponentTypeIndex<T>(m_ECSManager));
        }

        template<typename T>
        void RemoveComponentFromEntity(Scene::GameObject& someGameObject, const std::uint32_t someEntityID)
        {
            m_ECSManager.RemoveComponent<T>(someEntityID);
            RemoveComponentFromGameObjectData(someGameObject,
                m_ECSManager.GetComponentTypeIndex<T>());
        }

        void RemoveComponentFromEntityUsingTypeIndex(const std::uint32_t someEntityID,
            const std::size_t someComponentTypeIndex);

        void AddComponentToGameObjectData(Scene::GameObject& someGameObject, std::size_t someComponentTypeIndex);
        void RemoveComponentFromGameObjectData(Scene::GameObject& someGameObject, std::size_t someComponentTypeIndex);

        template<std::derived_from<Scene::GameObject> GameObjectType>
        GameObjectType* AddGameObject()
        {
            m_gameObjectsInScene.push_back(new GameObjectType());
            RegisterGameObject(m_gameObjectsInScene.back());
            return static_cast<GameObjectType*>(m_gameObjectsInScene.back());
        }

        void DeleteGameObject(Scene::GameObject* someGameObject);

        void UnTrackGameObject(Scene::GameObject* someGameObject);
        void CleanupScene();

    protected:
#ifdef _DEBUG
        virtual void SetDebugNames(){}
#endif

    private:
        void RegisterGameObject(Scene::GameObject* someGameObject);
        void RegisterComponents();

    protected:
        std::vector<Scene::GameObject*> m_gameObjectsInScene;

    private:
        ECS::ECSManager m_ECSManager;
    };
}
