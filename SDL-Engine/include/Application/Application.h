#pragma once
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

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

	static Application& GetInstance();

	void Init();
	void Run();

	[[nodiscard]] SDL_Window* GetMainWindow() const;
	[[nodiscard]] SDL_Renderer* GetMainRenderer() const;

	void SetBackgroundColor(const SDL_Color someColor)
	{
		m_backgroundColor = someColor;
	}

private:
	void InitiateShutdown();
	void RefreshBackground();
	void CheckForQuitEvent();
	void UpdateCoreSystems();

protected:
	SDL_Window* m_mainWindow = nullptr;
	SDL_Renderer* m_mainRenderer = nullptr;

private:
	SDL_Color m_backgroundColor = { 0, 0, 0, 255 };
	bool m_isRunning = true;
	SDL_Event m_mainEventCatcher = SDL_Event {};
};

Application& CreateApplication();





