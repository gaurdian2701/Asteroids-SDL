#pragma once
#include <string>
#include <unordered_map>
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

namespace Core::CoreSystems
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager();

		SDL_Texture* TryLoadAndGetTexture(const std::string someImageFilePath);
		SDL_Texture* GetTexture(const std::string someImageFilePath);
		void ClearData();

	private:
		std::unordered_map<std::string, SDL_Texture*> m_textureMap = std::unordered_map<std::string, SDL_Texture*>();
	};
}
