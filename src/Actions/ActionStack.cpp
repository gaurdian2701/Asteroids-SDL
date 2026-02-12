#include "Actions/ActionStack.h"
#include "Actions/IAction.h"

void Actions::ActionStack::PushAction(IAction* someAction)
{
    if (someAction != nullptr)
    {
        //remove instances of the action from the stack if any
        for (auto it = m_actionStack.begin(); it != m_actionStack.end(); ++it)
        {
            if (*it == someAction)
            {
                m_actionStack.erase(it);
            }
        }

        //push to the top of the stack, i.e. the end of the array
        m_actionStack.push_back(someAction);

        //reset current action
        if (m_currentAction != nullptr && m_currentAction != someAction)
        {
            m_currentAction = nullptr;
        }
    }
}

void Actions::ActionStack::RemoveAction(IAction* someAction)
{
    if (someAction != nullptr)
    {
        if (m_currentAction == someAction)
        {
            m_currentAction->OnEnd();
            m_currentAction = nullptr;
        }
        m_actionStack.erase(std::find(m_actionStack.begin(), m_actionStack.end(), someAction));
    }
}


void Actions::ActionStack::UpdateActions(const float deltaTime)
{
    //is the stack empty?
    if (m_actionStack.size() == 0)
    {
        return;
    }

    //Are we handling an action for the first time?
    while (m_currentAction == nullptr && !m_actionStack.empty())
    {
        m_currentAction = m_actionStack.back();

        //Call OnBegin() on the action, while passing a bFirstTime variable
        bool bisFirstTime = !m_firstTimeActions.contains(m_currentAction);
        m_firstTimeActions.insert(m_currentAction);
        m_currentAction->OnBegin(bisFirstTime);

        //Did OnBegin() push or remove some other action?
        if (m_currentAction != nullptr)
        {
            if (!m_actionStack.empty() && m_currentAction != m_actionStack.back())
            {
                m_currentAction = nullptr;
                UpdateActions(deltaTime);
                return;
            }
        }
    }

    //Call OnUpdate() on the actions
    if (m_currentAction != nullptr)
    {
        //Update action
        m_currentAction->OnUpdate(deltaTime);

        //Are we still the current action?
        if (!m_actionStack.empty() && m_currentAction == m_actionStack.back())
        {
            //Has the current action finished?
            if (m_currentAction->IsDone())
            {
                m_currentAction->OnEnd();
                m_actionStack.pop_back();
                m_firstTimeActions.erase(m_currentAction);
                m_currentAction = nullptr;
            }
        }
        else
        {
            m_currentAction = nullptr;
        }
    }
}

void Actions::ActionStack::End()
{
    for (auto it = m_actionStack.rbegin(); it != m_actionStack.rend(); ++it)
    {
        if (*it != nullptr)
        {
            (*it)->OnEnd();
            delete (*it);
        }
    }

    m_actionStack.clear();
}

