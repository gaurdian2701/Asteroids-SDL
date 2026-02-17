#pragma once
#include "vec2.hpp"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
    class IProjectile : public Scene::GameObject
    {
    public:
        IProjectile() = default;
        ~IProjectile() override = default;

    public:
        float m_speed = 300.0f;
        float m_scale = 50.0f;
        float m_startingRotation = 0.0f;
        glm::vec2 m_startingPosition = glm::vec2(0.0f);
        glm::vec2 m_movementDirection = glm::vec2(0.0f);
    };
}
