#include "GameObjects/SimpleChild.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"

const inline std::string ROCKET_BOOSTER_PARTICLE_FILEPATH = "images/img_fireCircle.png";

void Asteroids::GameObjects::SimpleChild::Start()
{
    AddComponent<Assets::Components::Transform>();
    AddComponent<Assets::Components::Renderer2D>();

    auto& t = GetComponent<Assets::Components::Transform>();

    if (m_parent != nullptr)
    {
        t.Parent = &m_parent->GetComponent<Assets::Components::Transform>();
        t.LocalScale = glm::vec2(10.0f, 10.0f);
    }

    auto& renderer = GetComponent<Assets::Components::Renderer2D>();
    renderer.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
    .TryLoadAndGetTexture(ROCKET_BOOSTER_PARTICLE_FILEPATH);
}
