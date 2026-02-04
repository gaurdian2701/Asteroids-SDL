#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"
#include "PrintDebug.h"

namespace Assets::Components
{
    struct Transform
    {
        //Default Constructor
        Transform()
        {
            PrintDebug("Transform default constructor called \n");
        }

        //Move Constructor
        Transform(Transform&& other) noexcept
        {
            PrintDebug("Transform move constructor called \n");

            PositionVector = other.PositionVector;
            ScaleFactor = other.ScaleFactor;
        }

        //Move Assignment operator
        Transform& operator=(Transform&& other) noexcept
        {
            PrintDebug("Transform move assignment constructor called \n");

            if (this != &other)
            {
                PositionVector = other.PositionVector;
                ScaleFactor = other.ScaleFactor;
            }
            return *this;
        }

        //Copy Constructor
        Transform(const Transform& other)
        {
            PrintDebug("Transform copy constructor called \n");

            PositionVector = other.PositionVector;
            ScaleFactor = other.ScaleFactor;
        }

        glm::vec2 PositionVector = glm::vec2(0.0f);
        glm::vec2 ScaleFactor = glm::vec2(1.0f);
        float Rotation = 0.0f;
    };
}
