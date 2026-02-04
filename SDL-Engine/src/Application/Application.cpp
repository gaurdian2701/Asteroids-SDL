#include "Application/Application.h"

#include <cassert>
#include <chrono>
#include <iostream>

#include <SDL3/SDL_init.h>

#include "PrintDebug.h"
#include "Core/CoreSystems/CoreSystemsHolder.h"


static Application* CoreApplicationInstance = nullptr;

const char* WINDOW_NAME = "Asteroids";

Application::Application()
{
    if (CoreApplicationInstance != nullptr)
    {
        PrintDebug("Application already exists!");
        return;
    }

    CoreApplicationInstance = this;

    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        PrintDebug("SDL_Init Error: %s", SDL_GetError());
        return;
    }

    m_mainWindow = SDL_CreateWindow(
        WINDOW_NAME,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    SDL_SetWindowMinimumSize(m_mainWindow, SCREEN_WIDTH, SCREEN_HEIGHT);

    m_mainRenderer = SDL_CreateRenderer(m_mainWindow, nullptr);

    assert(m_mainWindow != nullptr && "Window Creation Failed!");
}

Application::~Application()
{
    m_mainWindow = nullptr;
}

Application& Application::GetCoreInstance()
{
    return *CoreApplicationInstance;
}

void Application::Init()
{
    for (auto& system : Core::GetCoreSystems())
    {
        system->Initialize();
    }
}

void Application::InitiateShutdown()
{
    SDL_DestroyRenderer(m_mainRenderer);
    SDL_DestroyWindow(m_mainWindow);
    SDL_Quit();
}

void Application::Run()
{
    GetApplicationInstance()->BeginApplication();
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    SDL_zero(m_mainEventCatcher);
    SDL_SetRenderDrawBlendMode(m_mainRenderer, SDL_BLENDMODE_BLEND);

    while (m_isRunning)
    {
        CheckForQuitEvent();

        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        RefreshBackground();

        UpdateCoreSystems();
        GetApplicationInstance()->UpdateApplication(deltaTime.count());

        SDL_RenderPresent(m_mainRenderer);
    }

    GetApplicationInstance()->EndApplication();
    InitiateShutdown();
}

void Application::UpdateCoreSystems()
{
    for (auto& system : Core::GetCoreSystems())
    {
        system->Update();
    }
}


void Application::CheckForQuitEvent()
{
    while (SDL_PollEvent(&m_mainEventCatcher))
    {
        if (m_mainEventCatcher.type == SDL_EVENT_QUIT)
        {
            m_isRunning = false;
        }
    }
}

void Application::RefreshBackground()
{
    SDL_SetRenderDrawColor(m_mainRenderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    SDL_RenderClear(m_mainRenderer);
}

SDL_Window* Application::GetMainWindow() const
{
    return m_mainWindow;
}

SDL_Renderer* Application::GetMainRenderer() const
{
    return m_mainRenderer;
}




