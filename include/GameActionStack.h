#pragma once
#include "Actions/ActionStack.h"
#include "GameActions/GameSceneAction.h"

namespace Asteroids
{
    class GameActionStack : public Actions::ActionStack
    {
    public:
        GameActionStack() = default;
        ~GameActionStack() override = default;

        void Start();
        void Update(const float deltaTime);

        template<typename GameSceneType>
        void UnloadScene()
        {
            auto sceneAction = GetAction<GameActions::GameSceneAction<GameSceneType, 100>>();
            m_staleGameSceneToBeUpdated = sceneAction->m_gameSceneHeld;
            if (sceneAction != nullptr)
            {
                RemoveAction(sceneAction);
            }
        }

        template<typename GameSceneType>
        void LoadScene()
        {
            PushAction(new GameActions::GameSceneAction<GameSceneType, 100>());
        }

    private:
        void UpdateStaleScene(const float deltaTime);

    private:
        Core::GameScene* m_staleGameSceneToBeUpdated = nullptr;
    };
}
