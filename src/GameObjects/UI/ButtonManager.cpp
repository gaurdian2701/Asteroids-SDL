#include "GameObjects/UI/ButtonManager.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/InputSystem.h"
#include "GameObjects/UI/Button.h"

void Asteroids::GameObjects::ButtonManager::Start()
{
	RefreshButtons();

	if (m_buttonList.size() > 0)
	{
		m_selectedButton = m_buttonList[0];
		m_selectedButtonIndex = 1;
	}
}

void Asteroids::GameObjects::ButtonManager::Update(const float deltaTime)
{
	CheckForInput();
}

void Asteroids::GameObjects::ButtonManager::CheckForInput()
{
	//If Selected button index is zero, that means we have an empty button list
	//I am using index-1 to access elements

	if (m_selectedButtonIndex != 0)
	{
		if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_SPACE))
		{
			m_selectedButton->OnClick();
		}

		if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_DOWN))
		{
			m_selectedButtonIndex++;
			if (m_selectedButtonIndex == 0)
			{
				m_selectedButtonIndex = 1;
			}
		}
		
		if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_UP))
		{
			m_selectedButtonIndex--;
			if (m_selectedButtonIndex == 0)
			{
				m_selectedButtonIndex = m_buttonList.size();
			}
		}
		m_selectedButton->OnUnSelect();
		m_selectedButton = m_buttonList[(m_selectedButtonIndex-1) % m_buttonList.size()];
		m_selectedButton->OnSelect();
	}
}

void Asteroids::GameObjects::ButtonManager::RefreshButtons()
{
	for (uint8_t i = 0; i < m_buttonList.size(); i++)
	{
		auto button = m_buttonList[i];
		if (button != nullptr)
		{
			auto buttonTransform = button->GetComponent<Assets::Components::Transform>();
			if (buttonTransform != nullptr)
			{
				buttonTransform->LocalPosition = m_startingPositionForButtonList + glm::vec2(0.0f, -i * m_spacing);
			}
		}
	}
}

