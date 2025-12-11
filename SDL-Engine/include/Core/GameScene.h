#pragma once
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
        ~GameScene() = default;

        void Start();
        void Update(const float deltaTime);

        ECS::ECSManager& GetECSManager();

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
        void AddGameObject()
        {
            m_gameObjectsInScene.push_back(new GameObjectType());
            RegisterGameObject(m_gameObjectsInScene.back());
        }

        void DeleteGameObject(Scene::GameObject* someGameObject);

        void UnTrackGameObject(Scene::GameObject* someGameObject);
        void CleanupScene();

    private:
        void RegisterGameObject(Scene::GameObject* someGameObject);
        void StartGameObjects();
        void RegisterComponents();
        void UpdateGameObjects(const float deltaTime);
        void UpdateECSManager();

    private:
        ECS::ECSManager m_ECSManager;
        std::vector<Scene::GameObject*> m_gameObjectsInScene;
    };
}
