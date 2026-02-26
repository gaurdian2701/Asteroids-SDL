#pragma once
#include "Core/GameScene.h"
#include "GameObjects/UnitManager.h"

namespace Asteroids::GameScenes
{
	class MainMenuScene : public Core::GameScene
	{
	public:
		explicit MainMenuScene(int maxGameObjects) : GameScene(maxGameObjects){}
		~MainMenuScene() override = default;

		void CreateGameObjects() override;
	};
}
