#pragma once
#include <string>
#include <unordered_map>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

namespace Core::CoreSystems
{
	class TextureResourceManager
	{
	private:
		TextureResourceManager() = default;
		~TextureResourceManager();

	public:
		static TextureResourceManager& GetInstance()
		{
			static TextureResourceManager* instance = new TextureResourceManager();
			return *instance;
		}

		SDL_Texture* TryLoadAndGetTexture(const std::string someImageFilePath);
		SDL_Texture* GetTexture(const std::string someImageFilePath);

	private:
		std::unordered_map<std::string, SDL_Surface*> m_surfacesMap;
		std::unordered_map<std::string, SDL_Texture*> m_textureMap;
	};
}
