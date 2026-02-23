#pragma once
#include "Core/GameScene.h"

namespace Asteroids
{
    class GameActionStack;
}

namespace Core
{
    class GameScene;
}

namespace Actions
{
    class ActionStack;
}

class Application;

class Asteroids_App : public Application
{
public:
    Asteroids_App() = default;
    ~Asteroids_App() = default;

    void BeginApplication() override;
    void UpdateApplication(float deltaTime) override;
    void EndApplication() override;

    void NotifySceneForDelete(Core::GameScene* someScene);

private:
    void InitializeAppSystems();
    void StartGame();

public:
    Asteroids::GameActionStack* m_mainGameActionStack = nullptr;
};

inline Application* GetApplicationInstance()
{
    static Asteroids_App app;
    return &app;
}
