#pragma once
#include <iostream>
#include <mat4x4.hpp>
#include "gtc/quaternion.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/quaternion.hpp"
#include "ext/matrix_transform.hpp"

namespace Assets::Components
{
    struct Transform
    {
        //Default Constructor
        Transform()
        {
            std::cout << "Transform default constructor called \n" << std::flush;
        }

        //Move Constructor
        Transform(Transform&& other) noexcept
        {
            std::cout << "Transform move constructor called \n" << std::flush;

            PositionVector = other.PositionVector;
            ScaleFactor = other.ScaleFactor;
        }

        //Move Assignment operator
        Transform& operator=(Transform&& other) noexcept
        {
            std::cout << "Transform assignment operator called \n" << std::flush;

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
            std::cout << "Transform copy constructor called \n" << std::flush;
            PositionVector = other.PositionVector;
            ScaleFactor = other.ScaleFactor;
        }

        glm::vec2 PositionVector = glm::vec2(0.0f);
        glm::vec2 ScaleFactor = glm::vec2(1.0f);
        float Rotation = 0.0f;
    };
}
