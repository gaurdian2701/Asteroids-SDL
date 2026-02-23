#pragma once
#include "IControlAction.h"

namespace Asteroids::GameActions
{
    class PlayerControlAction : public IControlAction
    {
    public:
        PlayerControlAction() = default;
        ~PlayerControlAction() override = default;

        inline const float GetTranslationValue() override
        {
            return m_translationInput;
        }

        inline const float GetRotationValue() override
        {
            return m_rotationAngle;
        }

        inline const bool GetIsShooting()
        {
            return m_shootButtonPressed;
        }

        void OnUpdate(float deltaTime) override;
        bool IsDone() override;

    private:
        float m_translationInput = 0.0f;
        float m_rotationAngle = 0.0f;
        bool m_shootButtonPressed = false;
    };
}
