#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
    class SimpleChild : public Scene::GameObject
    {
    public:
        SimpleChild() = default;
        ~SimpleChild() override = default;

        void AddComponentsBeforeStartup() override;
        void Start() override;
    };
}
