#include "GameScenes/MainGameScene.h"
#include "Assets/Components/Transform.h"
#include "GameObjects/SpaceShipParticleEmitter.h"
#include "GameObjects/Player.h"
#include "GameObjects/UnitManager.h"
#include "GameObjects/PoolManager.h"
#include "GameObjects/UI/ScoreAndHealthUI.h"

void Asteroids::GameScenes::MainGameScene::CreateGameObjects()
{
    m_poolManager = AddGameObject<GameObjects::PoolManager>();
    m_spaceShip = AddGameObject<GameObjects::Player>();
    m_loneEmitter = AddGameObject<GameObjects::SpaceShipParticleEmitter>();
    m_unitManager = AddGameObject<GameObjects::UnitManager>();
    m_scoreUI = AddGameObject<GameObjects::ScoreAndHealthUI>();
}

void Asteroids::GameScenes::MainGameScene::InitializeGameObjectReferences()
{
    m_loneEmitter->GetComponent<Assets::Components::Transform>()->SetParent(m_spaceShip);
}
