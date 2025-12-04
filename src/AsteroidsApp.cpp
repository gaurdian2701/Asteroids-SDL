#include "AsteroidsApp.h"

#include "Core/AssetPathHolder.h"
#include "GameObjects/SpaceShip.h"
#include "Scene/GameObject.h"

void AsteroidsApp::Begin()
{
    InitializeSystems();
    InitializeObjects();
    StartScene();
}

void AsteroidsApp::InitializeSystems()
{
    Core::AssetPathHolder::GetInstance().UpdateAssetFolderPath("Assets/");
}

void AsteroidsApp::InitializeObjects()
{
    m_MainScene = new Core::GameScene(100);
    m_MainScene->AddGameObject<Assets::GameObjects::SpaceShip>();
}

void AsteroidsApp::StartScene()
{
    m_MainScene->Start();
}

void AsteroidsApp::Update(const float deltaTime)
{
    m_MainScene->Update(deltaTime);
}

void AsteroidsApp::End()
{

}