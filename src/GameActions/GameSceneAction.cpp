#include "GameActions/GameSceneAction.h"
#include <assert.h>

#include "Core/GameScene.h"

void Asteroids::GameActions::GameSceneAction::OnBegin(bool isFirstTime)
{
    assert(m_gameSceneHeld != nullptr);
    m_gameSceneHeld->InitializeScene();
    m_gameSceneHeld->Start();
}

void Asteroids::GameActions::GameSceneAction::OnUpdate(float deltaTime)
{
    m_gameSceneHeld->Update(deltaTime);
}

bool Asteroids::GameActions::GameSceneAction::IsDone()
{
    return m_sceneUnloadInitiated;
}

void Asteroids::GameActions::GameSceneAction::OnEnd()
{
    m_gameSceneHeld->CleanupScene();
    delete m_gameSceneHeld;
    m_gameSceneHeld = nullptr;
}

void Asteroids::GameActions::GameSceneAction::EndScene()
{
    m_sceneUnloadInitiated = true;
}





