#pragma once
#include "Actions/IAction.h"
#include <concepts>

namespace Core
{
    class GameScene;
}

namespace Asteroids::GameActions
{
    class GameSceneAction : public Actions::IAction
    {
    public:
        GameSceneAction() = default;
        ~GameSceneAction() override = default;

        template<std::derived_from<Core::GameScene> someGameSceneType, int numberOfEntities>
        void CreateScene()
        {
            m_gameSceneHeld = new someGameSceneType(numberOfEntities);
        }

        void OnBegin(bool isFirstTime) override;
        void OnUpdate(float deltaTime) override;
        bool IsDone() override;
        void OnEnd() override;

        void EndScene();

    protected:
        Core::GameScene* m_gameSceneHeld = nullptr;
        bool m_sceneUnloadInitiated = false;
    };
}
