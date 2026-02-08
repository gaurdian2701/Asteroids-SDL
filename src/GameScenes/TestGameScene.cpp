#include "GameScenes/TestGameScene.h"

#include "Assets/Components/Transform.h"
#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"
#include "GameObjects/SimpleChild.h"


void Asteroids::GameScenes::TestGameScene::CreateGameObjects()
{
    m_spaceShip = AddGameObject<GameObjects::SpaceShip>();
    m_loneEmitter = AddGameObject<GameObjects::LoneParticleEmitter>();
    m_simpleChild = AddGameObject<GameObjects::SimpleChild>();
}

void Asteroids::GameScenes::TestGameScene::InitializeGameObjects()
{
    m_loneEmitter->m_parent = m_spaceShip;
}

void Asteroids::GameScenes::TestGameScene::Start()
{
    GameScene::Start();
}

void Asteroids::GameScenes::TestGameScene::Update(const float deltaTime)
{
    GameScene::Update(deltaTime);
}

#ifdef _DEBUG
void Asteroids::GameScenes::TestGameScene::SetGameObjectDebugNames()
{
    m_spaceShip->m_name = "Space Ship";
    m_loneEmitter->m_name = "Lone Emitter";
    m_simpleChild->m_name = "Simple Child";
}
#endif


