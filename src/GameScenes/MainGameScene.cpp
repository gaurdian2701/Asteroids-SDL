#include "GameScenes/MainGameScene.h"
#include "Assets/Components/Transform.h"
#include "GameObjects/SpaceShipParticleEmitter.h"
#include "GameObjects/SpaceShip.h"
#include "GameObjects/UnitManager.h"
#include "GameObjects/PoolManager.h"

void Asteroids::GameScenes::MainGameScene::CreateGameObjects()
{
    m_poolManager = AddGameObject<GameObjects::PoolManager>();
    m_spaceShip = AddGameObject<GameObjects::SpaceShip>();
    m_loneEmitter = AddGameObject<GameObjects::SpaceShipParticleEmitter>();
    m_unitManager = AddGameObject<GameObjects::UnitManager>();
}

void Asteroids::GameScenes::MainGameScene::InitializeGameObjectReferences()
{
    m_loneEmitter->GetComponent<Assets::Components::Transform>()->SetParent(m_spaceShip);
}

void Asteroids::GameScenes::MainGameScene::Start()
{
    GameScene::Start();
}

void Asteroids::GameScenes::MainGameScene::Update(const float deltaTime)
{
    GameScene::Update(deltaTime);
}

