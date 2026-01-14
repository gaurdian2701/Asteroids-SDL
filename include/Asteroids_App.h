#pragma once
#include "SDLEngine.h"
#include "Core/GameScene.h"

class Application;

class Asteroids_App : public Application
{
public:
    Asteroids_App() = default;
    ~Asteroids_App() = default;

    void BeginApplication() override;
    void UpdateApplication(float deltaTime) override;
    void EndApplication() override;

private:
    void InitializeSystems();
    void InitializeObjects();
    void StartScene();

public:
    Core::GameScene* m_MainScene = nullptr;
};

inline Application* GetApplicationInstance()
{
    static Asteroids_App app;
    return &app;
}
