#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
    class SimpleChild : public Scene::GameObject
    {
    public:
        SimpleChild() = default;
        ~SimpleChild() override = default;

        void Start() override;

    public:
        GameObject* m_parent = nullptr;
    };
}
