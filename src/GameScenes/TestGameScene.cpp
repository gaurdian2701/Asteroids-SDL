#include "GameScenes/TestGameScene.h"

#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"

void Asteroids::GameScenes::TestGameScene::AddGameObjectsToScene()
{
    Scene::GameObject* spaceShip = AddGameObject<GameObjects::SpaceShip>();
    GameObjects::LoneParticleEmitter* emitter = AddGameObject<GameObjects::LoneParticleEmitter>();

    emitter->m_parent = spaceShip;
}
