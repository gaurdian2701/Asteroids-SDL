#pragma once
#include "Actions/ActionStack.h"

namespace Asteroids
{
    class GameActionStack : public Actions::ActionStack
    {
    public:
        GameActionStack() = default;
        ~GameActionStack() override = default;

        void Start();
        void Update(const float deltaTime);
    };
}
