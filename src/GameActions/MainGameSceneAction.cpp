#include "GameActions/MainGameSceneAction.h"

void Asteroids::GameActions::MainGameSceneAction::OnBegin(bool isFirstTime)
{
    if (isFirstTime)
    {
        m_mainGameScene = new GameScenes::MainGameScene(100);
        m_mainGameScene->InitializeScene();
        m_mainGameScene->Start();
    }
}

void Asteroids::GameActions::MainGameSceneAction::OnUpdate(const float deltaTime)
{
    m_mainGameScene->Update(deltaTime);
}

void Asteroids::GameActions::MainGameSceneAction::OnEnd()
{
    m_mainGameScene->CleanupScene();
}

bool Asteroids::GameActions::MainGameSceneAction::IsDone()
{
    return false;
}
