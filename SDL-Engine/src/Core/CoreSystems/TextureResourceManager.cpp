#include "Core/CoreSystems/TextureResourceManager.h"
#include "Application/Application.h"
#include "Core/AssetPathHolder.h"

Core::CoreSystems::TextureResourceManager::~TextureResourceManager()
{
	for (const auto& surface : m_surfacesMap)
	{
		SDL_DestroySurface(surface.second);
	}

	for (const auto& texture : m_textureMap)
	{
		SDL_DestroyTexture(texture.second);
	}
}

SDL_Texture* Core::CoreSystems::TextureResourceManager::TryLoadAndGetTexture(const std::string someImageFilePath)
{
	if (!m_surfacesMap.contains(someImageFilePath))
	{
		m_surfacesMap[someImageFilePath] = SDL_LoadPNG(
			AssetPathHolder::GetInstance().GetAssetPath(someImageFilePath).c_str());
		m_textureMap[someImageFilePath] = SDL_CreateTextureFromSurface(
			Application::GetCoreInstance().GetMainRenderer(),
			m_surfacesMap[someImageFilePath]);
	}

	return m_textureMap[someImageFilePath];
}

SDL_Texture* Core::CoreSystems::TextureResourceManager::GetTexture(const std::string someImageFilePath)
{
	return m_textureMap[someImageFilePath];
}

void Core::CoreSystems::TextureResourceManager::ClearData()
{
	m_textureMap.clear();
	m_surfacesMap.clear();
}




