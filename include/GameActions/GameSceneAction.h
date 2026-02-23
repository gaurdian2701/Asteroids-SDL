#pragma once
#include <cstdint>
#include "Actions/IAction.h"
#include "Core/GameScene.h"

namespace Asteroids::GameActions
{
    template<typename GameSceneType, std::uint32_t entityCount>
    class GameSceneAction : public Actions::IAction
    {
    public:
        GameSceneAction() = default;
        ~GameSceneAction() override = default;

        void OnBegin(bool isFirstTime) override
        {
            m_gameSceneHeld = new GameSceneType(entityCount);
            m_gameSceneHeld->InitializeScene();
            m_gameSceneHeld->Start();
        }

        void OnUpdate(float deltaTime) override
        {
            m_gameSceneHeld->Update(deltaTime);
        }

        bool IsDone() override
        {
            return m_sceneUnloadInitiated;
        }

        void OnEnd() override
        {
            m_gameSceneHeld->SetupForEnd();
            m_gameSceneHeld = nullptr;
        }

        void EndScene()
        {
            m_sceneUnloadInitiated = true;
        }

    public:
        GameSceneType* m_gameSceneHeld = nullptr;
        bool m_sceneUnloadInitiated = false;
    };
}
