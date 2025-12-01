#pragma once
#include <vector>
#include <memory>
#include <concepts>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"


namespace Core
{
	class Layer;
}

class Renderer;
class Window;

extern void BeginApplication();
extern void UpdateApplication(const float deltaTime);
extern void EndApplication();

class Application
{
public:
	Application();
	virtual ~Application();
	Application(const Application& other) = delete;

	static Application* GetInstance();

	void Init();
	void Run();

	std::vector<std::unique_ptr<Core::Layer>>& GetLayerList();
	SDL_Window* GetMainWindow() const;
	SDL_Renderer* GetMainRenderer() const;

	template<std::derived_from<Core::Layer> T, typename ... LayerArguments>
	void PushLayer(LayerArguments&& ... layerArguments)
	{
		LayerList.push_back(std::make_unique<T>(std::forward<LayerArguments>(layerArguments) ...));
	}

private:
	void PushLayers();
	void AttachAllLayers() const;
	void UpdateLayerList();
	void DetachAllLayers();
	void CloseGLFWWindow();
	void InitiateShutdown();

protected:
	SDL_Window* m_mainWindow = nullptr;
	SDL_Renderer* m_mainRenderer = nullptr;

private:
	std::vector<std::unique_ptr<Core::Layer>> LayerList;
};

Application& CreateApplication();





