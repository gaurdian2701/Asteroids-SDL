#pragma once
#include "Core/GameScene.h"

namespace Asteroids::GameObjects
{
    class EnemySpaceship;
    class SpaceShip;
    class SpaceShipParticleEmitter;
    class UnitManager;
    class PoolManager;
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

    private:
        GameObjects::PoolManager* m_poolManager = nullptr;
        GameObjects::SpaceShip* m_spaceShip = nullptr;
        GameObjects::SpaceShipParticleEmitter* m_loneEmitter = nullptr;
        GameObjects::UnitManager* m_unitManager = nullptr;
    };
}
