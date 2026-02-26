#pragma once
#include "UIText.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class ScoreAndHealthUI : public Scene::GameObject
	{
	public:
		ScoreAndHealthUI() = default;
		~ScoreAndHealthUI() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void End() override;

	private:
		void UpdateUI(UIText* uiText, std::string someText);
		void OnPlayerTookDamage();
		void OnPlayerScored();

	private:
		uint8_t m_maxLives = 3;
		uint8_t m_currentLives = m_maxLives;
		uint32_t m_damageEventID = 0;
		uint32_t m_scoreEventID = 0;
		std::string m_livesText = "LIVES: ";
		std::string m_scoreText = "SCORE: ";
		int m_currentScore = 0;
		glm::vec2 m_startingPosition = glm::vec2(-400.0f, 350.0f);
		SDL_Color m_livesTextColor = { 255, 255, 255, 255 };
		SDL_Color m_scoreTextColor = { 0, 255, 65, 255 };
		UIText* m_healthUI = nullptr;
		UIText* m_scoreUI = nullptr;
	};
}
