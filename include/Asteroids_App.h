#pragma once
#include "SDLEngine.h"
#include "Core/GameScene.h"

class Application;

class Asteroids_App : public Application
{
public:
    Asteroids_App() = default;
    ~Asteroids_App() = default;

    void Begin();
    void Update(float deltaTime);
    void End();

private:
    void InitializeSystems();
    void InitializeObjects();
    void StartScene();

public:
    Core::GameScene* m_MainScene = nullptr;
};

static Asteroids_App& GetApplicationInstance()
{
    static Asteroids_App app;
    return app;
}

inline Application& CreateApplication()
{
    return GetApplicationInstance();
}

inline void BeginApplication()
{
    GetApplicationInstance().Begin();
}

inline void UpdateApplication(const float deltaTime)
{
    GetApplicationInstance().Update(deltaTime);
}

inline void EndApplication()
{
    GetApplicationInstance().End();
}
