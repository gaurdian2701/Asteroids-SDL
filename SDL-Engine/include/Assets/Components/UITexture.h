#pragma once
#include "SDL3/SDL_render.h"

namespace Assets::Components
{
	struct UITexture
	{
		//Default Constructor
		UITexture() = default;
		~UITexture()
		{
			RenderTexture = nullptr;
		}

		//Copy Constructor
		UITexture(const UITexture& other)
		{
			Color = other.Color;
			RenderRectangle = other.RenderRectangle;
			RenderTexture = other.RenderTexture;
		}

		//Move Constructor
		UITexture(UITexture&& other) noexcept
		{
			Color = other.Color;
			RenderRectangle = other.RenderRectangle;
			RenderTexture = other.RenderTexture;
		}

		//Copy Assignment Operator
		UITexture& operator=(const UITexture& other)
		{
			if (this != &other)
			{
				Color = other.Color;
				RenderRectangle = other.RenderRectangle;
				RenderTexture = other.RenderTexture;
			}
			return *this;
		}

		//Move Assignment Operator
		UITexture& operator=(UITexture&& other) noexcept
		{
			if (this != &other)
			{
				Color = other.Color;
				RenderRectangle = other.RenderRectangle;
				RenderTexture = other.RenderTexture;
			}
			return *this;
		}

		SDL_FColor Color = SDL_FColor(255, 255, 255, 255);
		SDL_FRect RenderRectangle = SDL_FRect(0, 0, 5, 5);
		SDL_Texture* RenderTexture = nullptr;
		
	};
}
