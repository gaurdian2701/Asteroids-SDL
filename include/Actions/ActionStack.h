#pragma once
#include <unordered_set>
#include <vector>

namespace Actions
{
    class IAction;

    class ActionStack
    {
    public:
        ActionStack() = default;
        virtual ~ActionStack() = default;

        void UpdateActions(const float deltaTime);
        void PushAction(IAction* someAction);

    protected:
        IAction* m_currentAction = nullptr;
        std::vector<IAction*> m_actionStack = std::vector<IAction*>();
        std::unordered_set<IAction*> m_firstTimeActions = std::unordered_set<IAction*>();
    };
}
