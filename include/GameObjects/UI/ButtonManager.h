#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class Button;

	class ButtonManager : public Scene::GameObject
	{
	public:
		ButtonManager() = default;
		~ButtonManager() override = default;

		virtual void Start() override;
		void Update(const float deltaTime) override;
		void RefreshButtons();

	protected:
		virtual void CheckForInput();

	protected:
		uint8_t m_selectedButtonIndex = 0;
		Button* m_selectedButton = nullptr;

	public:
		float m_spacing = 100.0f;
		glm::vec2 m_startingPositionForButtonList = glm::vec2(0.0f);
		std::vector<Button*> m_buttonList = std::vector<Button*>();
	};
}
