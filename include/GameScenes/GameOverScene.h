#pragma once
#include "Core/GameScene.h"

namespace Asteroids::GameScenes
{
	class GameOverScene : public Core::GameScene
	{
	public:
		explicit GameOverScene(uint32_t maxGameObjects) : GameScene(maxGameObjects) {}
		~GameOverScene() override = default;
		void CreateGameObjects() override;
	};
}
