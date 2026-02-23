#include "GameActions/PlayerControlAction.h"
#include "Asteroids_App.h"
#include "GameActionStack.h"
#include "Core/CoreSystems/InputSystem.h"
#include "GameActions/GameSceneAction.h"
#include "GameScenes/MainGameScene.h"
#include "SDL3/SDL_scancode.h"

void Asteroids::GameActions::PlayerControlAction::OnUpdate(float deltaTime)
{
    m_translationInput = 0.0f;

    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_UP))
    {
        m_translationInput = 1.0f;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_LEFT))
    {
        m_rotationAngle += deltaTime;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_RIGHT))
    {
        m_rotationAngle -= deltaTime;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_SPACE))
    {
        m_shootButtonPressed = true;
    }
    else
    {
        m_shootButtonPressed = false;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_R))
    {
        GameActionStack* stack = static_cast<Asteroids_App*>(GetApplicationInstance())->m_mainGameActionStack;
        stack->UnloadScene<GameScenes::MainGameScene>();
        stack->LoadScene<GameScenes::MainGameScene>();
    }
}

bool Asteroids::GameActions::PlayerControlAction::IsDone()
{
    return false;
}
