#include "GameScenes/MainGameScene.h"

#include "Assets/Components/Transform.h"
#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"
#include "GameObjects/UnitManager.h"


void Asteroids::GameScenes::MainGameScene::CreateGameObjects()
{
    m_spaceShip = AddGameObject<GameObjects::SpaceShip>();
    m_loneEmitter = AddGameObject<GameObjects::LoneParticleEmitter>();
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

#ifdef _DEBUG
void Asteroids::GameScenes::MainGameScene::SetGameObjectDebugNames()
{
    m_spaceShip->m_name = "Space Ship";
    m_loneEmitter->m_name = "Lone Emitter";
    m_unitManager->m_name = "Unit Manager";
}
#endif


