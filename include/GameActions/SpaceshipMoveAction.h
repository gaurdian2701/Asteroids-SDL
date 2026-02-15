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

namespace Scene
{
    class GameObject;
}

namespace Asteroids::GameActions
{
    class SpaceshipMoveAction : public Actions::IAction
    {
    public:
        explicit SpaceshipMoveAction(
            PlayerInputAction* somePlayerInputAction,
            Scene::GameObject* someSpaceShip) :
        m_playerInputAction(somePlayerInputAction),
        m_spaceshipGameObject(someSpaceShip)
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
        Scene::GameObject* m_spaceshipGameObject = nullptr;
        PlayerInputAction* m_playerInputAction = nullptr;
    };
}
