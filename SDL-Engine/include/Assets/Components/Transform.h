#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "gtc/quaternion.hpp"
#include "PrintDebug.h"
#include "Scene/GameObject.h"

namespace Assets::Components
{
    struct Transform
    {
        ~Transform()
        {
            Parent = nullptr;
        }

        //Default Constructor
        Transform()
        {
            PrintDebug("Transform default constructor called \n");
        }

        //Copy Constructor
        Transform(const Transform& other)
        {
            PrintDebug("Transform copy constructor called \n");

            WorldPosition = other.WorldPosition;
            WorldScale = other.WorldScale;
            WorldRotation = other.WorldRotation;

            LocalPosition = other.LocalPosition;
            LocalScale = other.LocalScale;
            LocalRotation = other.LocalRotation;

            Parent = other.Parent;
            Owner = other.Owner;
        }

        //Move Constructor
        Transform(Transform&& other) noexcept
        {
            PrintDebug("Transform move constructor called \n");

            WorldPosition = other.WorldPosition;
            WorldScale = other.WorldScale;
            WorldRotation = other.WorldRotation;

            LocalPosition = other.LocalPosition;
            LocalScale = other.LocalScale;
            LocalRotation = other.LocalRotation;

            Parent = other.Parent;
            Owner = other.Owner;
        }

        //Copy Assignment operator
        Transform& operator=(const Transform& other)
        {
            WorldPosition = other.WorldPosition;
            WorldScale = other.WorldScale;
            WorldRotation = other.WorldRotation;

            LocalPosition = other.LocalPosition;
            LocalScale = other.LocalScale;
            LocalRotation = other.LocalRotation;

            Parent = other.Parent;
            Owner = other.Owner;
        }

        //Move Assignment operator
        Transform& operator=(Transform&& other) noexcept
        {
            PrintDebug("Transform move assignment constructor called \n");

            if (this != &other)
            {
                WorldPosition = other.WorldPosition;
                WorldScale = other.WorldScale;
                WorldRotation = other.WorldRotation;

                LocalPosition = other.LocalPosition;
                LocalScale = other.LocalScale;
                LocalRotation = other.LocalRotation;

                Parent = other.Parent;
                Owner = other.Owner;
            }
            return *this;
        }

        Transform* Parent = nullptr;

        glm::vec2 WorldPosition = glm::vec2(0.0f);
        glm::vec2 WorldScale = glm::vec2(1.0f);
        float WorldRotation = 0.0f;

        glm::vec2 LocalPosition = glm::vec2(0.0f);
        glm::vec2 LocalScale = glm::vec2(1.0f);
        float LocalRotation = 0.0f;

        Scene::GameObject* Owner = nullptr;

    };
}
