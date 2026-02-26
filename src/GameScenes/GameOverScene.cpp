#include "GameScenes/GameOverScene.h"
#include "Asteroids_App.h"
#include "GameActionStack.h"
#include "Assets/Components/Transform.h"
#include "GameObjects/UI/Button.h"
#include "GameObjects/UI/ButtonManager.h"
#include "GameObjects/UI/UIText.h"
#include "GameScenes/MainGameScene.h"

const inline std::string TEXT_FONT_PATH = "fonts/font_Arcade.ttf";

void Asteroids::GameScenes::GameOverScene::CreateGameObjects()
{
	GameObjects::UIText* scoreText = AddGameObject<GameObjects::UIText>();
	scoreText->SetFont(TEXT_FONT_PATH.c_str(), 24);
	scoreText->SetText("SCORE: " + std::to_string(static_cast<Asteroids_App*>(GetApplicationInstance())->m_playerScore));
	if (auto scoreTransform = scoreText->GetComponent<Assets::Components::Transform>())
	{
		scoreTransform->LocalPosition = glm::vec2(0.0f, 200.0f);
	}

	GameObjects::Button* restartButton = AddGameObject<GameObjects::Button>();
	GameObjects::Button* quitButton = AddGameObject<GameObjects::Button>();

	restartButton->SetFont(TEXT_FONT_PATH.c_str(), 30.0f);
	quitButton->SetFont(TEXT_FONT_PATH.c_str(), 30.0f);

	restartButton->SetText("RESTART");
	quitButton->SetText("QUIT GAME");

	restartButton->SetOnClickFunction(
	[&]()
	{
		GameActionStack* stack = static_cast<Asteroids_App*>(GetApplicationInstance())->m_mainGameActionStack;
		if (stack != nullptr)
		{
			stack->UnloadScene<GameOverScene>();
			stack->LoadScene<MainGameScene>();
		}
	});

	quitButton->SetOnClickFunction(
		[&]()
		{
			Application::GetCoreInstance().EndApplication();
		});

	GameObjects::ButtonManager* buttonManager = AddGameObject<GameObjects::ButtonManager>();

	buttonManager->m_buttonList.push_back(restartButton);
	buttonManager->m_buttonList.push_back(quitButton);
}
