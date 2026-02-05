#pragma once
#include "Core/GameScene.h"
#include "GameObjects/SpaceShip.h"

namespace Asteroids::GameObjects
{
    class SpaceShip;
    class SimpleChild;
    class LoneParticleEmitter;
}

namespace Asteroids::GameScenes
{
    class TestGameScene : public Core::GameScene
    {
    public:
        explicit TestGameScene(int maxGameObjects) : GameScene(maxGameObjects) {}
        ~TestGameScene() override  = default;
        void Update(const float deltaTime) override;
        void InitializeGameObjects() override;

        protected:
#ifdef _DEBUG
        void SetDebugNames() override;
#endif
    private:
#ifdef _DEBUG
        void UpdateImGuiDebugs();
#endif

    private:
        GameObjects::SpaceShip* m_spaceShip = nullptr;
        GameObjects::LoneParticleEmitter* m_loneEmitter = nullptr;
        GameObjects::SimpleChild* m_simpleChild = nullptr;
    };
}
