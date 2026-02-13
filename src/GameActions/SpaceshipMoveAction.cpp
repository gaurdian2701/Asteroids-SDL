#include "GameActions/SpaceshipMoveAction.h"

#include <algorithm>
#include <__msvc_ranges_to.hpp>

#include "GameActions/PlayerInputAction.h"
#include "Assets/Components/Transform.h"
#include "vec2.hpp"

void Asteroids::GameActions::SpaceshipMoveAction::OnUpdate(float deltaTime)
{
    m_playerInputAction->OnUpdate(deltaTime);

    const float translationInput = m_playerInputAction->GetTranslationInput();
    glm::vec2 positionPreviousFrame = m_spaceShipTransform->LocalPosition;

    if (translationInput > 0.1f)
    {
        m_spaceShipTransform->LocalPosition += m_spaceShipTransform->Up * m_currentMoveSpeed * deltaTime;
        m_spaceShipVelocity = m_spaceShipTransform->LocalPosition - positionPreviousFrame;
        m_currentMoveSpeed += m_acceleration * deltaTime;
    }
    else
    {
        if (m_currentMoveSpeed > 0.0f)
        {
            m_residualMoveSpeed = m_currentMoveSpeed;
        }

        if (glm::length(m_spaceShipTransform->LocalPosition) > 0.0f)
        {
            m_spaceShipTransform->LocalPosition += glm::normalize(m_spaceShipVelocity) * m_residualMoveSpeed * deltaTime;
        }
        m_currentMoveSpeed = 0.0f;
    }

    m_currentMoveSpeed = std::clamp(m_currentMoveSpeed, 0.0f, m_maxMoveSpeed);
    m_spaceShipTransform->LocalRotation = m_playerInputAction->GetRotationAngle() * m_rotationSpeed;
}

bool Asteroids::GameActions::SpaceshipMoveAction::IsDone()
{
    return false;
}
