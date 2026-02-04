#include "Core/GameScene.h"
#include "Assets/Components/ParticleEmitter.h"
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
	m_ECSManager.RegisterComponent<Assets::Components::ParticleEmitter>();
}

void Core::GameScene::RegisterGameObject(Scene::GameObject *someGameObject)
{
	someGameObject->m_sceneReference = this;
	someGameObject->m_entityID = GetECSManager().GenerateEntityID();
}

void Core::GameScene::RemoveComponentFromEntityUsingTypeIndex(const std::uint32_t someEntityID,
	const std::size_t someComponentTypeIndex)
{
	m_ECSManager.GetComponentRemovalHandlesArray()[someComponentTypeIndex](m_ECSManager, someEntityID);
}

void Core::GameScene::AddComponentToGameObjectData(Scene::GameObject &someGameObject,
	const std::size_t someComponentTypeIndex)
{
	someGameObject.m_componentBitSet[someComponentTypeIndex] = true;
}

void Core::GameScene::RemoveComponentFromGameObjectData(Scene::GameObject &someGameObject,
	const std::size_t someComponentTypeIndex)
{
	someGameObject.m_componentBitSet[someComponentTypeIndex] = false;
}


void Core::GameScene::Start()
{
	//Start GameObjects
	for (auto& gameObject : m_gameObjectsInScene)
	{
		gameObject->Start();
	}

	//Start ECS Systems
	m_ECSManager.BeginSystems();
}

void Core::GameScene::Update(const float deltaTime)
{
	//Update GameObjects
	for (auto& gameObject : m_gameObjectsInScene)
	{
		gameObject->Update(deltaTime);
	}

	//Update ECS Manager
	m_ECSManager.UpdateManager(deltaTime);
}



Core::ECS::ECSManager& Core::GameScene::GetECSManager()
{
	return m_ECSManager;
}

void Core::GameScene::DeleteGameObject(Scene::GameObject* someGameObject)
{
	//Use Component ID to remove components from gameobject, hence untracking them in the ECS
	for (std::size_t typeIndex = 0; typeIndex < Core::ECS::MAX_COMPONENT_TYPES; typeIndex++)
	{
		if (someGameObject->m_componentBitSet[typeIndex])
		{
			RemoveComponentFromEntityUsingTypeIndex(someGameObject->m_entityID, typeIndex);
		}
	}

	m_ECSManager.FreeEntityID(someGameObject->GetEntityID()); //Untrack entityID
	someGameObject->m_sceneReference = nullptr;

	//Remove from scene list
	int gameObjectIndexInSceneList = 0;
	for (const auto gameObject : m_gameObjectsInScene)
	{
		if (gameObject->GetEntityID() == someGameObject->GetEntityID())
		{
			break;
		}
		gameObjectIndexInSceneList++;
	}
	m_gameObjectsInScene.erase(m_gameObjectsInScene.begin() + gameObjectIndexInSceneList);

	delete someGameObject;
}

void Core::GameScene::UnTrackGameObject(Scene::GameObject* someGameObject)
{
	m_ECSManager.FreeEntityID(someGameObject->GetEntityID());
}

void Core::GameScene::CleanupScene()
{
	for (const auto gameObject : m_gameObjectsInScene)
	{
		DeleteGameObject(gameObject);
	}
}

