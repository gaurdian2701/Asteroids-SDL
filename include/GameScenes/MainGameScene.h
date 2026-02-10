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
    class MainGameScene : public Core::GameScene
    {
    public:
        explicit MainGameScene(int maxGameObjects) : GameScene(maxGameObjects) {}
        ~MainGameScene() override  = default;
        void CreateGameObjects() override;
        void InitializeGameObjectReferences() override;
        void Start() override;
        void Update(const float deltaTime) override;
#ifdef _DEBUG
        void SetGameObjectDebugNames() override;
#endif

    private:
        GameObjects::SpaceShip* m_spaceShip = nullptr;
        GameObjects::LoneParticleEmitter* m_loneEmitter = nullptr;
        GameObjects::LoneParticleEmitter* m_secondEmitter = nullptr;
        GameObjects::SimpleChild* m_simpleChild = nullptr;
    };
}
