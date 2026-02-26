#include "GameObjects/UI/UIText.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/UITexture.h"

const inline std::string TEXT_FONT_PATH = "fonts/font_Arcade.ttf";

void Asteroids::GameObjects::UIText::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::UITexture>();
}

void Asteroids::GameObjects::UIText::Start()
{
	auto transform = GetComponent<Assets::Components::Transform>();
	transform->LocalScale = glm::vec2(100.0f, 50.0f);

	auto uiTexture = GetComponent<Assets::Components::UITexture>();
	uiTexture->TextFont = GetSceneReference().GetResourceManager().TryLoadAndGetFont(
		TEXT_FONT_PATH, 24);

#ifdef _DEBUG
	m_name = "UI Text";
#endif
}

void Asteroids::GameObjects::UIText::SetFont(const char *pathToFont, float fontSize)
{
	if (auto uiTexture = GetComponent<Assets::Components::UITexture>())
	{
		uiTexture->TextFont = GetSceneReference().GetResourceManager().TryLoadAndGetFont(
			pathToFont, fontSize);
	}
}

void Asteroids::GameObjects::UIText::SetText(const std::string &text)
{
	if (auto uiTexture = GetComponent<Assets::Components::UITexture>())
	{
		uiTexture->SetFontText(text, std::forward<SDL_Color>(m_color));
	}
}
