#include "GameActions/PlayerInputAction.h"
#include "Core/CoreSystems/InputSystem.h"
#include "SDL3/SDL_scancode.h"

void Asteroids::GameActions::PlayerInputAction::OnUpdate(float deltaTime)
{
    m_translationInput = 0.0f;

    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_W))
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
}

bool Asteroids::GameActions::PlayerInputAction::IsDone()
{
    return false;
}

bool Asteroids::GameActions::PlayerInputAction::NoInputTaken()
{
    return m_translationInput > -0.01f && m_translationInput < 0.01f;
}

