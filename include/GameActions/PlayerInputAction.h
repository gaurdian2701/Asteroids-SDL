#pragma once
#include "Actions/IAction.h"

namespace Asteroids::GameActions
{
    class PlayerInputAction : public Actions::IAction
    {
    public:
        PlayerInputAction() = default;
        ~PlayerInputAction() override = default;

        inline const float GetTranslationInput()
        {
            return m_translationInput;
        }

        inline float GetRotationAngle()
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
