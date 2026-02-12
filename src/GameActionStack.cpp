#include "GameActionStack.h"
#include "GameActions/GameSceneAction.h"
#include "GameScenes/MainGameScene.h"

void Asteroids::GameActionStack::Start()
{
    PushAction(new GameActions::GameSceneAction());
    auto gameSceneAction = dynamic_cast<GameActions::GameSceneAction*>(GetAction<GameActions::GameSceneAction>());
    gameSceneAction->CreateScene<GameScenes::MainGameScene, 100>();
}

void Asteroids::GameActionStack::Update(const float deltaTime)
{
    UpdateActions(deltaTime);
}

