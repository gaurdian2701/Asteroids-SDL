#include "../../../include/GameObjects/UI/Button.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/UITexture.h"

const inline std::string BLANK_IMAGE_FILEPATH = "images/img_blank.png";

void Asteroids::GameObjects::Button::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::UITexture>();
	AddComponent<Assets::Components::Renderer2D>();
}

void Asteroids::GameObjects::Button::Start()
{
	auto transform = GetComponent<Assets::Components::Transform>();
	transform->LocalScale = glm::vec2(100.0f, 50.0f);

	auto renderer = GetComponent<Assets::Components::Renderer2D>();
	renderer->RenderTexture = GetSceneReference().GetResourceManager().TryLoadAndGetTexture(
		BLANK_IMAGE_FILEPATH);
	renderer->Color = SDL_FColor{0, 0, 0, 255};
}

void Asteroids::GameObjects::Button::SetOnClickFunction(std::function<void()> function)
{
	OnClickFunction = function;
}

void Asteroids::GameObjects::Button::SetBackGroundColor(SDL_FColor color)
{
	if (auto renderer = GetComponent<Assets::Components::Renderer2D>())
	{
		renderer->Color = color;
	}
}

void Asteroids::GameObjects::Button::OnSelect()
{
	SetBackGroundColor(m_onSelectBackgroundColor);
}

void Asteroids::GameObjects::Button::OnUnSelect()
{
	SetBackGroundColor(m_onUnSelectBackgroundColor);
}

void Asteroids::GameObjects::Button::OnClick()
{
	OnClickFunction();
}





