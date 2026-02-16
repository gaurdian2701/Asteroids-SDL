#include "GameActions/SpaceshipMoveAction.h"
#include <algorithm>
#include "GameActions/PlayerControlAction.h"
#include "Assets/Components/Transform.h"
#include "vec2.hpp"

void Asteroids::GameActions::SpaceshipMoveAction::OnUpdate(float deltaTime)
{
    m_playerInputAction->OnUpdate(deltaTime);

    auto transform = m_spaceshipGameObject->GetComponent<Assets::Components::Transform>();
    const float translationInput = m_playerInputAction->GetTranslationInput();
    glm::vec2 positionPreviousFrame = transform->LocalPosition;

    if (translationInput > 0.1f)
    {
        transform->LocalPosition += transform->Up * m_currentMoveSpeed * deltaTime;

        if (glm::length(m_residualVelocity) > 0.0f) {
            transform->LocalPosition += glm::normalize(m_residualVelocity) * m_residualSpeed * deltaTime;
        }
        m_spaceShipVelocity = transform->LocalPosition - positionPreviousFrame;
        m_currentMoveSpeed += m_acceleration * deltaTime;
        m_residualSpeed -= m_acceleration * deltaTime;
    }
    else
    {
        if (m_currentMoveSpeed > 0.0f)
        {
            m_residualSpeed = m_currentMoveSpeed;
            m_residualVelocity = m_spaceShipVelocity;
        }

        if (glm::length(m_residualVelocity) > 0.0f)
        {
            transform->LocalPosition += glm::normalize(m_residualVelocity) * m_residualSpeed * deltaTime;
            m_residualSpeed -= m_acceleration * deltaTime;
        }
        m_currentMoveSpeed = 0.0f;
    }

    m_currentMoveSpeed = std::clamp(m_currentMoveSpeed, 0.0f, m_maxMoveSpeed);
    m_residualSpeed = std::clamp(m_residualSpeed, 0.0f, m_maxMoveSpeed);
    transform->LocalRotation = m_playerInputAction->GetRotationAngle() * m_rotationSpeed;
}

bool Asteroids::GameActions::SpaceshipMoveAction::IsDone()
{
    return false;
}
