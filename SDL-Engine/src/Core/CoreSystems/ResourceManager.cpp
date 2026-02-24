#include "Core/CoreSystems/ResourceManager.h"
#include "Application/Application.h"
#include "Core/AssetPathHolder.h"
#include "SDL3/SDL_oldnames.h"

Core::CoreSystems::ResourceManager::~ResourceManager()
{
	for (const auto& texture : m_textureMap)
	{
		SDL_DestroyTexture(texture.second);
	}
}

SDL_Texture* Core::CoreSystems::ResourceManager::TryLoadAndGetTexture(const std::string someImageFilePath)
{
	if (!m_textureMap.contains(someImageFilePath))
	{
		SDL_Surface* surface = SDL_LoadPNG(
			AssetPathHolder::GetInstance().GetAssetPath(someImageFilePath).c_str());
		m_textureMap[someImageFilePath] = SDL_CreateTextureFromSurface(
			Application::GetCoreInstance().GetMainRenderer(),
			surface);
		SDL_DestroySurface(surface);
	}

	return m_textureMap[someImageFilePath];
}

SDL_Texture* Core::CoreSystems::ResourceManager::GetTexture(const std::string someImageFilePath)
{
	return m_textureMap[someImageFilePath];
}

void Core::CoreSystems::ResourceManager::ClearData()
{
	m_textureMap.clear();
}




