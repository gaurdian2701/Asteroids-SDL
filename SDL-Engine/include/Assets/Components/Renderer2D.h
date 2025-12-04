#pragma once
#include "SDL3/SDL_render.h"

namespace Assets::Components
{
    struct Renderer2D
    {
        //Default Constructor
        Renderer2D() = default;
        ~Renderer2D()
        {
            RenderTexture = nullptr;
        }

        //Move Constructor
        Renderer2D(Renderer2D&& other) noexcept
        {
            Color = other.Color;
        }

        //Move Assignment Operator
        Renderer2D& operator=(Renderer2D&& other) noexcept
        {
            if (this != &other)
            {
                Color = other.Color;
            }

            return *this;
        }

        //Copy Constructor
        Renderer2D(const Renderer2D& other)
        {
            Color = other.Color;
        }

        SDL_FColor Color = SDL_FColor(255, 255, 255, 255);
        SDL_FRect RenderRectangle = SDL_FRect(0, 0, 5, 5);
        SDL_Texture* RenderTexture = nullptr;
    };
}
