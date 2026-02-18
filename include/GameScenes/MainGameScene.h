#pragma once
#include "Core/GameScene.h"

namespace Asteroids::GameObjects
{
    class SpaceShip;
    class LoneParticleEmitter;
    class UnitManager;
    class ProjectilePool;
}

namespace Asteroids::GameScenes
{
    class MainGameScene : public Core::GameScene
    {
    public:
        explicit MainGameScene(int maxGameObjects) : GameScene(maxGameObjects) {}
        ~MainGameScene() override
        {
            m_spaceShip = nullptr;
            m_loneEmitter = nullptr;
        }

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
        GameObjects::UnitManager* m_unitManager = nullptr;
        GameObjects::ProjectilePool* m_projectilePool = nullptr;
    };
}
