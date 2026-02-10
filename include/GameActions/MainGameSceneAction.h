#pragma once
#include "Actions/IAction.h"
#include "GameScenes/MainGameScene.h"

namespace Asteroids::GameActions
{
    class MainGameSceneAction : public Actions::IAction
    {
    public:
        MainGameSceneAction() = default;
        ~MainGameSceneAction() override = default;

        void OnBegin(bool isFirstTime) override;
        void OnUpdate(float deltaTime) override;
        void OnEnd() override;
        bool IsDone() override;

    private:
        GameScenes::MainGameScene* m_mainGameScene = nullptr;
    };
}
