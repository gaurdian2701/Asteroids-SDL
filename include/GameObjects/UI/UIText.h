#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class UIText : public Scene::GameObject
	{
	public:
		UIText() = default;
		~UIText() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;

		void SetFont(const char* pathToFont, float fontSize);
		void SetText(const std::string& text);

	public:
		SDL_Color m_color = { 255, 255, 255, 255 };
	};
}
