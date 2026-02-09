#include "Asteroids_App.h"
#include "Core/AssetPathHolder.h"
#include "Scene/GameObject.h"
#include "GameScenes/MainGameScene.h"

void Asteroids_App::BeginApplication()
{
    InitializeAppSystems();
    InitializeScene();
    StartScene();
}

void Asteroids_App::InitializeAppSystems()
{
    Core::AssetPathHolder::GetInstance().UpdateAssetFolderPath("Assets/");
}

void Asteroids_App::InitializeScene()
{
    m_MainScene = new Asteroids::GameScenes::MainGameScene(100);
    m_MainScene->CreateGameObjects();
    m_MainScene->AddComponentsBeforeStartup();
    m_MainScene->InitializeGameObjectReferences();
#ifdef _DEBUG
    m_MainScene->SetGameObjectDebugNames();
#endif
}

void Asteroids_App::StartScene()
{
    m_MainScene->Start();
}

void Asteroids_App::UpdateApplication(const float deltaTime)
{
    m_MainScene->Update(deltaTime);
    m_MainScene->GarbageCollect();
}

void Asteroids_App::EndApplication()
{
    m_MainScene->CleanupScene();
}