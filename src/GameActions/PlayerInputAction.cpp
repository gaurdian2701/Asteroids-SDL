#include "GameActions/PlayerInputAction.h"
#include "Core/CoreSystems/InputSystem.h"
#include "SDL3/SDL_scancode.h"

void Asteroids::GameActions::PlayerInputAction::OnUpdate(float deltaTime)
{
    m_translationVector.x = 0;
    m_translationVector.y = 0;

    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_D))
    {
        m_translationVector.x = 1;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_A))
    {
        m_translationVector.x = -1;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_W))
    {
        m_translationVector.y = 1;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_S))
    {
        m_translationVector.y = -1;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_LEFT))
    {
        m_rotationAngle += m_rotationSpeed * deltaTime;
    }
    if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_RIGHT))
    {
        m_rotationAngle -= m_rotationSpeed * deltaTime;
    }
}

bool Asteroids::GameActions::PlayerInputAction::IsDone()
{
    return false;
}
