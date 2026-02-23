#include "Asteroids_App.h"
#include "GameActionStack.h"
#include "Core/AssetPathHolder.h"

void Asteroids_App::BeginApplication()
{
    InitializeAppSystems();
    StartGame();
}

void Asteroids_App::InitializeAppSystems()
{
    Core::AssetPathHolder::GetInstance().UpdateAssetFolderPath("Assets/");
}

void Asteroids_App::StartGame()
{
    m_mainGameActionStack = new Asteroids::GameActionStack();
    m_mainGameActionStack->Start();
}

void Asteroids_App::UpdateApplication(const float deltaTime)
{
    m_mainGameActionStack->Update(deltaTime);
}

void Asteroids_App::EndApplication()
{
    m_mainGameActionStack->End();
}

void Asteroids_App::NotifySceneForDelete(Core::GameScene *someScene)
{
    if (someScene != nullptr)
    {
        delete someScene;
    }
}

