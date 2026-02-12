#include "GameActions/SpaceshipMoveAction.h"

#include <algorithm>

#include "GameActions/PlayerInputAction.h"
#include "Assets/Components/Transform.h"
#include "vec2.hpp"

void Asteroids::GameActions::SpaceshipMoveAction::OnUpdate(float deltaTime)
{
    m_playerInputAction->OnUpdate(deltaTime);

    const glm::vec2 translationVector = m_playerInputAction->GetTranslationVector();

    m_spaceShipTransform->LocalPosition.x += translationVector.x * m_moveSpeed * deltaTime;
    m_spaceShipTransform->LocalPosition.y += translationVector.y * m_moveSpeed * deltaTime;

    m_spaceShipTransform->LocalRotation = m_playerInputAction->GetRotationAngle();
}

void Asteroids::GameActions::SpaceshipMoveAction::SlowdownShip(const float deltaTime)
{
}

bool Asteroids::GameActions::SpaceshipMoveAction::IsDone()
{
    return false;
}
