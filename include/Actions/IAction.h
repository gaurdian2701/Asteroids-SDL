#pragma once

namespace Actions
{
    class IAction
    {
    public:
        IAction() = default;
        virtual ~IAction() = default;
        virtual void OnBegin(bool isFirstTime){}
        virtual void OnUpdate(float deltaTime){}
        virtual void OnEnd(){}
        virtual bool IsDone(){ return false;}
    };
}