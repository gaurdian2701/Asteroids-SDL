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

        void OnBegin(bool isFirstTime) override{}
        void OnUpdate(float deltaTime) override;
        void OnEnd() override{}
        bool IsDone() override;
        bool NoInputTaken();

    private:
        float m_translationInput = 0.0f;
        float m_rotationAngle = 0.0f;
    };
}
