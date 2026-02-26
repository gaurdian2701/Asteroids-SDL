#include "GameScenes/MainMenuScene.h"
#include "Asteroids_App.h"
#include "GameActionStack.h"
#include "GameScenes/MainGameScene.h"
#include "GameObjects/UI/Button.h"
#include "GameObjects/UI/ButtonManager.h"

const inline std::string TEXT_FONT_PATH = "fonts/font_Arcade.ttf";

void Asteroids::GameScenes::MainMenuScene::CreateGameObjects()
{
	GameObjects::Button* startButton = AddGameObject<GameObjects::Button>();
	GameObjects::Button* quitButton = AddGameObject<GameObjects::Button>();

	//Set fonts for the buttons
	startButton->SetFont(TEXT_FONT_PATH.c_str(), 30.0f);
	quitButton->SetFont(TEXT_FONT_PATH.c_str(), 30.0f);

	startButton->SetText("START GAME");
	quitButton->SetText("QUIT GAME");

	startButton->SetOnClickFunction(
		[&]()
		{
			GameActionStack* stack = static_cast<Asteroids_App*>(GetApplicationInstance())->m_mainGameActionStack;
			if (stack != nullptr)
			{
				stack->UnloadScene<GameScenes::MainMenuScene>();
				stack->LoadScene<GameScenes::MainGameScene>();
			}
		});

	quitButton->SetOnClickFunction(
	[&]()
	{
		Application::GetCoreInstance().EndApplication();
	});

	GameObjects::ButtonManager* buttonManager = AddGameObject<GameObjects::ButtonManager>();

	buttonManager->m_buttonList.push_back(startButton);
	buttonManager->m_buttonList.push_back(quitButton);
}
