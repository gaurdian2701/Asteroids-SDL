#include "GameActionStack.h"
#include "GameActions/GameSceneAction.h"
#include "GameScenes/MainGameScene.h"

void Asteroids::GameActionStack::Start()
{
    PushAction(new GameActions::GameSceneAction<GameScenes::MainGameScene, 100>());
}

void Asteroids::GameActionStack::UpdateStaleScene(const float deltaTime)
{
    if (m_staleGameSceneToBeUpdated != nullptr)
    {
        m_staleGameSceneToBeUpdated->Update(deltaTime);
        m_staleGameSceneToBeUpdated = nullptr;
    }
}


void Asteroids::GameActionStack::Update(const float deltaTime)
{
    UpdateStaleScene(deltaTime);
    UpdateActions(deltaTime);
}



