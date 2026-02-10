#include "GameScenes/MainGameScene.h"

#include "Assets/Components/Transform.h"
#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"
#include "GameObjects/SimpleChild.h"


void Asteroids::GameScenes::MainGameScene::CreateGameObjects()
{
    m_spaceShip = AddGameObject<GameObjects::SpaceShip>();
    m_loneEmitter = AddGameObject<GameObjects::LoneParticleEmitter>();
    m_secondEmitter = AddGameObject<GameObjects::LoneParticleEmitter>();
    m_simpleChild = AddGameObject<GameObjects::SimpleChild>();
}

void Asteroids::GameScenes::MainGameScene::InitializeGameObjectReferences()
{
    m_loneEmitter->m_parent = m_spaceShip;
    m_secondEmitter->m_parent = m_loneEmitter;
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
    m_secondEmitter->m_name = "Second Emitter";
    m_simpleChild->m_name = "Simple Child";
}
#endif


