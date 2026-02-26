#pragma once
#include <functional>

#include "UIText.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class Button : public UIText
	{
	public:
		Button() = default;
		~Button() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void SetBackGroundColor(SDL_FColor color);
		void SetOnClickFunction(std::function<void()> function);
		void OnUnSelect();
		void OnSelect();
		void OnClick();

	public:
		SDL_FColor m_onSelectBackgroundColor = SDL_FColor{0, 0, 255, 255};
		SDL_FColor m_onUnSelectBackgroundColor = SDL_FColor{0, 0, 0, 255};

	private:
		std::function<void()> OnClickFunction = nullptr;
	};
}
