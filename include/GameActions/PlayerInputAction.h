#pragma once
#include "vec2.hpp"
#include "Actions/IAction.h"

namespace Asteroids::GameActions
{
    class PlayerInputAction : public Actions::IAction
    {
    public:
        explicit PlayerInputAction(float someRotationSpeed) : m_rotationSpeed(someRotationSpeed) {}
        ~PlayerInputAction() override = default;

        inline const glm::vec2& GetTranslationVector()
        {
            return m_translationVector;
        }

        inline float GetRotationAngle()
        {
            return m_rotationAngle;
        }

        void OnBegin(bool isFirstTime) override{}
        void OnUpdate(float deltaTime) override;
        void OnEnd() override{}
        bool IsDone() override;

    private:
        glm::vec2 m_translationVector = glm::vec2(0.0f);
        float m_rotationAngle = 0.0f;
        float m_rotationSpeed = 0.0f;
    };
}
