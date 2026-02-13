#pragma once
#include "vec2.hpp"
#include "Actions/IAction.h"

namespace Asteroids::GameActions
{
    class PlayerInputAction;
}

namespace Assets::Components
{
    struct Transform;
}

namespace Asteroids::GameActions
{
    class SpaceshipMoveAction : public Actions::IAction
    {
    public:
        explicit SpaceshipMoveAction(
            PlayerInputAction* somePlayerInputAction,
            Assets::Components::Transform* someTransform) :
        m_playerInputAction(somePlayerInputAction),
        m_spaceShipTransform(someTransform)
        {}

        ~SpaceshipMoveAction() override = default;

        void OnBegin(bool isFirstTime) override{}
        void OnUpdate(float deltaTime) override;
        void OnEnd() override{}
        bool IsDone() override;

    private:
        float m_currentMoveSpeed = 0.0f;
        float m_maxMoveSpeed = 200.0f;
        float m_acceleration = 100.0f;
        float m_deceleration = 200.0f;
        float m_rotationSpeed = 5.0f;
        float m_residualMoveSpeed = 0.0f;
        glm::vec2 m_spaceShipVelocity = glm::vec2(0.0f);
        Assets::Components::Transform* m_spaceShipTransform = nullptr;
        PlayerInputAction* m_playerInputAction = nullptr;
    };
}
