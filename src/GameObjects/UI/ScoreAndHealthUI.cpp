#include "GameObjects/UI/ScoreAndHealthUI.h"
#include "Asteroids_App.h"
#include "GameActionStack.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/UITexture.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "GameEvents/GameEvents.h"
#include "GameScenes/GameOverScene.h"
#include "GameScenes/MainGameScene.h"

const inline std::string TEXT_FONT_PATH = "fonts/font_Arcade.ttf";

void Asteroids::GameObjects::ScoreAndHealthUI::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
}

void Asteroids::GameObjects::ScoreAndHealthUI::Start()
{
	auto transform = GetComponent<Assets::Components::Transform>();

	transform->LocalPosition = glm::vec2(0.0f, 200.0f);

	m_healthUI = GetSceneReference().AddGameObject<UIText>();
	m_scoreUI = GetSceneReference().AddGameObject<UIText>();

	if (auto healthTransform = m_healthUI->GetComponent<Assets::Components::Transform>())
	{
		healthTransform->SetParent(this);
		healthTransform->LocalPosition = glm::vec2(-400.0f, 150.0f);
	}

	if (auto scoreTransform = m_scoreUI->GetComponent<Assets::Components::Transform>())
	{
		scoreTransform->SetParent(this);
		scoreTransform->LocalPosition = glm::vec2(400.0f, 150.0f);
	}

	m_healthUI->SetFont(TEXT_FONT_PATH.c_str(), 24);
	m_healthUI->SetText(m_livesText + std::to_string(m_currentLives));

	m_scoreUI->m_color = SDL_Color{ 0, 255, 65, 255 };
	m_scoreUI->SetFont(TEXT_FONT_PATH.c_str(), 24);
	m_scoreUI->SetText(m_scoreText + std::to_string(m_currentScore));

	Core::Events::EventSystem::GetInstance().RegisterEvent<GameEvents::PlayerTookDamageEvent>(
		Core::Events::EventType::GameEvent);
	Core::Events::EventSystem::GetInstance().RegisterEvent<GameEvents::PlayerScoredEvent>(
		Core::Events::EventType::GameEvent);

	m_damageEventID = Core::Events::EventSystem::GetInstance().SubscribeToEvent<GameEvents::PlayerTookDamageEvent>(
		Core::Events::EventType::GameEvent,
		[this](const std::any &eventPayload)
		{
			this->OnPlayerTookDamage();
		});

	m_scoreEventID = Core::Events::EventSystem::GetInstance().SubscribeToEvent<GameEvents::PlayerScoredEvent>(
		Core::Events::EventType::GameEvent,
		[this](const std::any &eventPayload)
		{
			this->OnPlayerScored();
		});

#ifdef _DEBUG
	m_name = "Score And Health UI";
#endif
}

void Asteroids::GameObjects::ScoreAndHealthUI::OnPlayerTookDamage()
{
	m_currentLives--;
	UpdateUI(m_healthUI, m_livesText + std::to_string(m_currentLives));

	if (m_currentLives == 0)
	{
		Asteroids_App* app = static_cast<Asteroids_App*>(GetApplicationInstance());
		app->m_playerScore = m_currentScore;

		GameActionStack* stack = app->m_mainGameActionStack;
		stack->UnloadScene<GameScenes::MainGameScene>();
		stack->LoadScene<GameScenes::GameOverScene>();
	}
}

void Asteroids::GameObjects::ScoreAndHealthUI::OnPlayerScored()
{
	m_currentScore += 10;
	UpdateUI(m_scoreUI, m_scoreText + std::to_string(m_currentScore));
}

void Asteroids::GameObjects::ScoreAndHealthUI::UpdateUI(UIText* uiText, std::string someText)
{
	if (uiText != nullptr)
	{
		uiText->SetText(someText);
	}
}

void Asteroids::GameObjects::ScoreAndHealthUI::End()
{
	Core::Events::EventSystem::GetInstance().UnsubscribeFromEvent<GameEvents::PlayerTookDamageEvent>(
		Core::Events::EventType::GameEvent, m_damageEventID);
	Core::Events::EventSystem::GetInstance().UnsubscribeFromEvent<GameEvents::PlayerScoredEvent>(
	Core::Events::EventType::GameEvent, m_scoreEventID);

	Core::Events::EventSystem::GetInstance().UnRegisterEvent<GameEvents::PlayerTookDamageEvent>(
		Core::Events::EventType::GameEvent);
	Core::Events::EventSystem::GetInstance().UnRegisterEvent<GameEvents::PlayerScoredEvent>(
		Core::Events::EventType::GameEvent);
}
