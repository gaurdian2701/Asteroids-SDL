#include "GameActions/PlayerControlAction.h"
#include "Core/CoreSystems/InputSystem.h"
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
}

bool Asteroids::GameActions::PlayerControlAction::IsDone()
{
    return false;
}

bool Asteroids::GameActions::PlayerControlAction::NoInputTaken()
{
    return m_translationInput > -0.01f && m_translationInput < 0.01f;
}

