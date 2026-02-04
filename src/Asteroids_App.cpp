#include "Asteroids_App.h"
#include "Core/AssetPathHolder.h"
#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"
#include "Scene/GameObject.h"
#include "GameScenes/TestGameScene.h"

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
    m_MainScene = new Asteroids::GameScenes::TestGameScene(100);
    m_MainScene->AddGameObjectsToScene();
}

void Asteroids_App::StartScene()
{
    m_MainScene->Start();
}

void Asteroids_App::UpdateApplication(const float deltaTime)
{
    m_MainScene->Update(deltaTime);
}

void Asteroids_App::EndApplication()
{
    m_MainScene->CleanupScene();
}