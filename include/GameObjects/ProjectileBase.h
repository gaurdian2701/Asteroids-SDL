#pragma once
#include "vec2.hpp"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"

namespace Assets::Components
{
    struct Collider2D;
}

namespace Asteroids::GameObjects
{
    class ProjectileBase : public Scene::GameObject
    {
    public:
        ProjectileBase() = default;
        ~ProjectileBase() override = default;

        void AddComponentsBeforeStartup() override;
        void Start() override;
        void Update(const float deltaTime) override;

        void Initialize(GameObject* instigator, glm::vec2&& somePosition, glm::vec2&& someMovementDirection, SDL_Texture* someTexture, float someRotation)
        {
            m_instigator = instigator;
            m_transform = GetComponent<Assets::Components::Transform>();
            m_transform->LocalScale = glm::vec2(m_scale);
            m_transform->LocalPosition = somePosition;
            m_transform->LocalRotation = someRotation;

            auto renderer = GetComponent<Assets::Components::Renderer2D>();
            renderer->RenderTexture = someTexture;
            m_movementDirection = someMovementDirection;
            m_isActive = true;
        }

        virtual void DisableProjectile(){}
        virtual void CheckForCollisions(){}

    protected:
        float m_speed = 300.0f;
        float m_scale = 50.0f;
        float m_startingRotation = 0.0f;
        float m_activeRadius = 600.0f;
        GameObject* m_instigator = nullptr;
        Assets::Components::Transform* m_transform = nullptr;
        Assets::Components::Collider2D* m_collider = nullptr;
        glm::vec2 m_movementDirection = glm::vec2(0.0f);
    };
}
