#include "GameScenes/TestGameScene.h"

#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"

void Asteroids::GameScenes::TestGameScene::AddGameObjectsToScene()
{
    AddGameObject<GameObjects::SpaceShip>();
    AddGameObject<GameObjects::LoneParticleEmitter>();
}
