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

        template<std::derived_from<Scene::GameObject> GameObjectType>
        void AddGameObject()
        {
            m_gameObjectsInScene.push_back(new GameObjectType());
            RegisterGameObject(m_gameObjectsInScene.back());
        }

        void UnTrackGameObject(Scene::GameObject* gameObject);

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
