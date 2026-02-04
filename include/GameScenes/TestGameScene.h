#pragma once
#include "Core/GameScene.h"

namespace Asteroids::GameScenes
{
    class TestGameScene : public Core::GameScene
    {
    public:
        explicit TestGameScene(int maxGameObjects) : GameScene(maxGameObjects) {}
        ~TestGameScene() = default;

        void AddGameObjectsToScene() override;
    };
}
