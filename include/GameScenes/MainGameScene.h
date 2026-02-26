#pragma once
#include "Core/GameScene.h"

namespace Asteroids::GameObjects
{
    class Enemyship;
    class Player;
    class SpaceShipParticleEmitter;
    class UnitManager;
    class PoolManager;
    class ScoreAndHealthUI;
}

namespace Asteroids::GameScenes
{
    class MainGameScene : public Core::GameScene
    {
    public:
        explicit MainGameScene(int maxGameObjects) : GameScene(maxGameObjects) {}
        ~MainGameScene() override
        {
            m_poolManager = nullptr;
            m_spaceShip = nullptr;
            m_loneEmitter = nullptr;
            m_unitManager = nullptr;
            m_scoreUI = nullptr;
        }

        void CreateGameObjects() override;
        void InitializeGameObjectReferences() override;

    private:
        GameObjects::PoolManager* m_poolManager = nullptr;
        GameObjects::Player* m_spaceShip = nullptr;
        GameObjects::SpaceShipParticleEmitter* m_loneEmitter = nullptr;
        GameObjects::UnitManager* m_unitManager = nullptr;
        GameObjects::ScoreAndHealthUI* m_scoreUI = nullptr;
    };
}
