#include "Asteroids_App.h"
#include "Core/AssetPathHolder.h"
#include "GameObjects/SpaceShip.h"
#include "Scene/GameObject.h"

void Asteroids_App::Begin()
{
    InitializeSystems();
    InitializeObjects();
    StartScene();
}

void Asteroids_App::InitializeSystems()
{
    Core::AssetPathHolder::GetInstance().UpdateAssetFolderPath("Assets/");
}

void Asteroids_App::InitializeObjects()
{
    m_MainScene = new Core::GameScene(100);
    m_MainScene->AddGameObject<Asteroids::GameObjects::SpaceShip>();
}

void Asteroids_App::StartScene()
{
    m_MainScene->Start();
}

void Asteroids_App::Update(const float deltaTime)
{
    m_MainScene->Update(deltaTime);
}

void Asteroids_App::End()
{
    m_MainScene->CleanupScene();
}