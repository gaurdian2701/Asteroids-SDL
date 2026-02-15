#include "Core/GameScene.h"
#include <filesystem>
#include "Assets/Components/ParticleEmitter.h"
#include "Scene/GameObject.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/Renderer2D.h"
#include "imgui.h"

const inline float LOCAL_SCALING_FACTOR = 0.01f;

Core::GameScene::GameScene(const std::uint32_t maxEntitiesInScene) : m_ECSManager(maxEntitiesInScene)
{
	m_gameObjectsInScene.reserve(maxEntitiesInScene);
	RegisterComponents();
	m_ECSManager.InitializeManager();
}

void Core::GameScene::InitializeScene()
{
	CreateGameObjects();
	InitializeGameObjectReferences();
#ifdef _DEBUG
	SetGameObjectDebugNames();
#endif
}

void Core::GameScene::RegisterComponents()
{
	m_ECSManager.RegisterComponent<Assets::Components::Transform>();
	m_ECSManager.RegisterComponent<Assets::Components::Renderer2D>();
	m_ECSManager.RegisterComponent<Assets::Components::ParticleEmitter>();
}

void Core::GameScene::InitializeGameObject(Scene::GameObject *someGameObject)
{
	someGameObject->m_sceneReference = this;
	someGameObject->m_entityID = GetECSManager().GenerateEntityID();
	someGameObject->AddComponentsBeforeStartup();
	m_startQueue.push_back(someGameObject);
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
	for (auto gameObject : m_gameObjectsInScene)
	{
		gameObject->Start();
		auto gameObjectInQueue = std::find(m_startQueue.begin(), m_startQueue.end(), gameObject);
		if (*gameObjectInQueue != nullptr && gameObjectInQueue != m_startQueue.end())
		{
			m_startQueue.erase(gameObjectInQueue);
		}
	}

	//Start ECS Systems
	m_ECSManager.BeginSystems();
}

void Core::GameScene::Update(const float deltaTime)
{
	//Start any newly created GameObjects
	for (auto gameObject : m_startQueue)
	{
		gameObject->Start();
	}

	//Update GameObjects
	for (auto gameObject : m_gameObjectsInScene)
	{
		gameObject->Update(deltaTime);
	}

	//Update ECS Manager
	m_ECSManager.UpdateManager(deltaTime);

#ifdef _DEBUG
	UpdateImGuiDebugs();
#endif

	GarbageCollect();
}

Core::ECS::ECSManager& Core::GameScene::GetECSManager()
{
	return m_ECSManager;
}

void Core::GameScene::DeleteGameObject(Scene::GameObject* someGameObject)
{
	//Use Component ID to remove components from gameobject, hence untracking them in the ECS
	for (std::size_t typeIndex = 0; typeIndex < MAX_COMPONENT_TYPES; typeIndex++)
	{
		if (someGameObject->m_componentBitSet[typeIndex])
		{
			RemoveComponentFromEntityUsingTypeIndex(someGameObject->m_entityID, typeIndex);
			someGameObject->m_componentBitSet[typeIndex] = false;
		}
	}

	UnTrackGameObject(someGameObject); //Untrack entityID
	someGameObject->m_sceneReference = nullptr;

	//Remove from scene list
	int gameObjectIndexInSceneList = 0;
	for (const auto gameObject : m_gameObjectsInScene)
	{
		if (gameObject != nullptr && gameObject->GetEntityID() == someGameObject->GetEntityID())
		{
			break;
		}
		gameObjectIndexInSceneList++;
	}

	//Set gameobject reference to nullptr and cleanup after
	m_gameObjectsInScene[gameObjectIndexInSceneList] = nullptr;
	delete someGameObject;
}

void Core::GameScene::UnTrackGameObject(Scene::GameObject* someGameObject)
{
	m_ECSManager.FreeEntityID(someGameObject->GetEntityID());
}

void Core::GameScene::GarbageCollect()
{
	//Erase any gameobjects that are deleted from the scene list
	int gameObjectIndexInSceneList = 0;
	std::vector<Scene::GameObject*>::const_iterator first = m_gameObjectsInScene.begin();

	for (auto& gameObject : m_gameObjectsInScene)
	{
		if (gameObject == nullptr)
		{
			m_gameObjectsInScene.erase(first + gameObjectIndexInSceneList);
		}
		gameObjectIndexInSceneList++;
	}

	//Clear the start queue
	if (!m_startQueue.empty())
	{
		m_startQueue.clear();
	}
}

void Core::GameScene::CleanupScene()
{
	for (auto& gameObject : m_gameObjectsInScene)
	{
		DeleteGameObject(gameObject);
	}

	m_gameObjectsInScene.erase(m_gameObjectsInScene.begin(), m_gameObjectsInScene.end());
}

#ifdef _DEBUG
void Core::GameScene::UpdateImGuiDebugs()
{
	ImGui::Begin("Debug");
	ImGui::Text("FRAME RATE:");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)\n",
	1000.0f / ImGui::GetIO().Framerate,
	ImGui::GetIO().Framerate);

	ImGui::Text("CHANGEABLE DEBUGS: ");

	for (auto& gameObject: m_gameObjectsInScene)
	{
		Assets::Components::Transform* transform = gameObject->GetComponent<Assets::Components::Transform>();

		if (transform != nullptr)
		{
			ImGui::PushID(gameObject->m_entityID);
			ImGui::Text(gameObject->m_name.c_str());
			ImGui::DragFloat2("Position", &transform->LocalPosition.x, 0.5f, -100.0f, 100.0f);
			ImGui::DragFloat2("Scale", &transform->LocalScale.x, 0.5f, -100.0f, 100.0f);
			ImGui::DragFloat("Rotation", &transform->LocalRotation, 0.5f, -100.0f, 100.0f);
			ImGui::Separator();
			ImGui::PopID();
		}
	}
	ImGui::End();
}
#endif


