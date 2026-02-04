#include "Asteroids_App.h"
#include "Core/AssetPathHolder.h"
#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"
#include "Scene/GameObject.h"

void Asteroids_App::BeginApplication()
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
    m_MainScene->AddGameObject<Asteroids::GameObjects::LoneParticleEmitter>();
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