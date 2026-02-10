#pragma once

namespace Actions
{
    class IAction
    {
    public:
        IAction() = default;
        virtual ~IAction() = default;
        virtual void OnBegin(bool isFirstTime) = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnEnd() = 0;
        virtual bool IsDone() = 0;
    };
}