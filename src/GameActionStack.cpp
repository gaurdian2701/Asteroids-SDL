#include "GameActionStack.h"
#include "GameActions/MainGameSceneAction.h"

void Asteroids::GameActionStack::Start()
{
    PushAction(new GameActions::MainGameSceneAction());
}

void Asteroids::GameActionStack::Update(const float deltaTime)
{
    UpdateActions(deltaTime);
}

void Asteroids::GameActionStack::End()
{

}

