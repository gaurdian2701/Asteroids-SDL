#include "Core/GameScene.h"
#include "Scene/GameObject.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/Renderer2D.h"

Core::GameScene::GameScene(const std::uint32_t maxEntitiesInScene) : m_ECSManager(maxEntitiesInScene)
{
	m_gameObjectsInScene.reserve(maxEntitiesInScene);
	RegisterComponents();
	m_ECSManager.InitializeManager();
}

void Core::GameScene::RegisterComponents()
{
	m_ECSManager.RegisterComponent<Assets::Components::Transform>();
	m_ECSManager.RegisterComponent<Assets::Components::Renderer2D>();
}

void Core::GameScene::RegisterGameObject(Scene::GameObject *someGameObject)
{
	someGameObject->m_sceneReference = this;
	someGameObject->m_entityID = GetECSManager().GenerateEntityID();
}

void Core::GameScene::Start()
{
	StartGameObjects();
}

void Core::GameScene::StartGameObjects()
{
	for (auto& gameObject : m_gameObjectsInScene)
	{
		gameObject->Start();
	}
}

void Core::GameScene::Update(const float deltaTime)
{
	UpdateGameObjects(deltaTime);
	UpdateECSManager();
}

void Core::GameScene::UpdateGameObjects(const float deltaTime)
{
	for (auto& gameObject : m_gameObjectsInScene)
	{
		gameObject->Update(deltaTime);
	}
}

void Core::GameScene::UpdateECSManager()
{
	m_ECSManager.UpdateManager();
}

Core::ECS::ECSManager& Core::GameScene::GetECSManager()
{
	return m_ECSManager;
}

void Core::GameScene::UnTrackGameObject(Scene::GameObject* gameObject)
{
	m_ECSManager.FreeEntityID(gameObject->GetEntityID());
}
