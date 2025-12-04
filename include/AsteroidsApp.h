#pragma once
#include "SDLEngine.h"
#include "Core/GameScene.h"

class Application;

class AsteroidsApp : public Application
{
public:
    AsteroidsApp() = default;
    ~AsteroidsApp() = default;

    void Begin();
    void Update(const float deltaTime);
    void End();

private:
    void InitializeSystems();
    void InitializeObjects();
    void StartScene();

public:
    Core::GameScene* m_MainScene = nullptr;
};

static AsteroidsApp& GetApplicationInstance()
{
    static AsteroidsApp app;
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
