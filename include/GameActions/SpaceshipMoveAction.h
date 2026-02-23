#pragma once
#include "vec2.hpp"
#include "Actions/IAction.h"
#include "PlayerControlAction.h"

namespace Asteroids::GameActions
{
    class PlayerControlAction;
}

namespace Assets::Components
{
    struct Transform;
}

namespace Scene
{
    class GameObject;
}

namespace Asteroids::GameActions
{
    class SpaceshipMoveAction : public Actions::IAction
    {
    public:
        explicit SpaceshipMoveAction(float someMaxMoveSpeed,
            float someAcceleration,
            float someRotationSpeed,
            IControlAction* somePlayerInputAction,
            Scene::GameObject* spaceShip) :
        m_maxMoveSpeed(someMaxMoveSpeed), m_acceleration(someAcceleration), m_rotationSpeed(someRotationSpeed),
        m_controlAction(somePlayerInputAction), m_spaceShip(spaceShip)
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
        float m_rotationSpeed = 5.0f;
        float m_residualSpeed = 0.0f;
        glm::vec2 m_residualVelocity = glm::vec2(0.0f);
        glm::vec2 m_spaceShipVelocity = glm::vec2(0.0f);
        IControlAction* m_controlAction = nullptr;
        Scene::GameObject* m_spaceShip = nullptr;
    };
}
