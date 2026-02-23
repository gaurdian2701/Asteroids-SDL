#pragma once
#include <unordered_set>
#include <vector>
#include <concepts>
#include <typeindex>
#include "Actions/IAction.h"

namespace Actions
{

    class ActionStack
    {
    public:
        ActionStack() = default;
        virtual ~ActionStack() = default;

        template<std::derived_from<IAction> ActionType>
        ActionType* GetAction()
        {
            auto actionFound = std::find_if(m_actionStack.begin(), m_actionStack.end(),
                [](IAction* actionToBeFound)
                {
                    return typeid(*actionToBeFound) == typeid(ActionType);
                });

            if (actionFound != m_actionStack.end())
            {
                return static_cast<ActionType*>(*actionFound);
            }
            return nullptr;
        }

        void UpdateActions(const float deltaTime);
        void PushAction(IAction* someAction);
        void RemoveAction(IAction* someAction);
        void End();

    protected:
        IAction* m_currentAction = nullptr;
        std::vector<IAction*> m_actionStack = std::vector<IAction*>();
        std::unordered_set<IAction*> m_firstTimeActions = std::unordered_set<IAction*>();
    };
}
