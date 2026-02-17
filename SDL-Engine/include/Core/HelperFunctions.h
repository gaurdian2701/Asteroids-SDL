#pragma once
#include "vec2.hpp"
#include "Application/Application.h"

namespace Core
{
    static inline glm::vec2 ConvertToScreenCoordinates(glm::vec2 someCartesianCoordinates)
    {
        return glm::vec2(someCartesianCoordinates.x + Application::SCREEN_WIDTH / 2,
            Application::SCREEN_HEIGHT/2 - someCartesianCoordinates.y);
    }

    static inline const glm::vec2& GetMaxCartesianLimits()
    {
        static glm::vec2 limits = glm::vec2(Application::SCREEN_WIDTH - Application::SCREEN_WIDTH/2,
            -Application::SCREEN_HEIGHT + Application::SCREEN_HEIGHT/2);
        return limits;
    }

    static inline const glm::vec2& GetMinCartesianLimits()
    {
        static glm::vec2 limits = glm::vec2(-Application::SCREEN_WIDTH/2,Application::SCREEN_HEIGHT/2);
        return limits;
    }
}
