#pragma once
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
            Assets::Components::Transform* someTransform,
            float someMoveSpeed) :
        m_playerInputAction(somePlayerInputAction),
        m_spaceShipTransform(someTransform),
        m_moveSpeed(someMoveSpeed)
        {}

        ~SpaceshipMoveAction() override = default;

        void OnBegin(bool isFirstTime) override{}
        void OnUpdate(float deltaTime) override;
        void OnEnd() override{}
        bool IsDone() override;

    private:
        float m_moveSpeed = 0.0f;
        float m_currentAcceleration = 0.0f;
        float m_maxAcceleration = 50.0f;
        Assets::Components::Transform* m_spaceShipTransform = nullptr;
        PlayerInputAction* m_playerInputAction = nullptr;
    };
}
