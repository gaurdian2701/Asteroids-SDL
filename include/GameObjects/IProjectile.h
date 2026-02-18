#pragma once
#include "vec2.hpp"
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
    class IProjectile : public Scene::GameObject
    {
    public:
        IProjectile() = default;
        ~IProjectile() override = default;

        void Initialize(glm::vec2&& somePosition, glm::vec2&& someMovementDirection, float someRotation)
        {
            auto transform = GetComponent<Assets::Components::Transform>();
            transform->LocalScale = glm::vec2(m_scale);
            transform->LocalPosition = somePosition;
            transform->LocalRotation = someRotation;
            m_movementDirection = someMovementDirection;
            m_isActive = true;
        }

    public:
        bool m_isActive = true;

    protected:
        float m_speed = 300.0f;
        float m_scale = 50.0f;
        float m_startingRotation = 0.0f;
        glm::vec2 m_movementDirection = glm::vec2(0.0f);
    };
}
