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
	AddComponentsBeforeStartup();
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

void Core::GameScene::RegisterGameObject(Scene::GameObject *someGameObject)
{
	someGameObject->m_sceneReference = this;
	someGameObject->m_entityID = GetECSManager().GenerateEntityID();
}

void Core::GameScene::AddComponentsBeforeStartup()
{
	for (auto& gameObject : m_gameObjectsInScene)
	{
		gameObject->AddComponentsBeforeStartup();
	}
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
	for (std::size_t typeIndex = 0; typeIndex < Core::ECS::MAX_COMPONENT_TYPES; typeIndex++)
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
		auto& transform = gameObject->GetComponent<Assets::Components::Transform>();

		ImGui::PushID(gameObject->m_name.c_str());
		ImGui::Text(gameObject->m_name.c_str());
		ImGui::SliderFloat2("Local Position", &transform.LocalPosition.x, -1000.0f, 1000.0f);
		ImGui::SliderFloat2("Local Scale", &transform.LocalScale.x, -100.0f, 100.0f);
		ImGui::SliderFloat("Local Rotation", &transform.LocalRotation, -1000.0f, 1000.0f);
		ImGui::Separator();
		ImGui::PopID();
	}
	ImGui::End();
}
#endif


