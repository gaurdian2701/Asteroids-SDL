#include "GameObjects/SimpleChild.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"

const inline std::string TEXTURE_FILEPATH = "images/img_spaceship.png";


void Asteroids::GameObjects::SimpleChild::AddComponentsBeforeStartup()
{
    AddComponent<Assets::Components::Transform>();
    AddComponent<Assets::Components::Renderer2D>();
}

void Asteroids::GameObjects::SimpleChild::Start()
{
    GameObject::Start();

    auto& transform = GetComponent<Assets::Components::Transform>();
    transform.LocalPosition = glm::vec2(0.0f, -1.0f);
    transform.LocalScale = glm::vec2(1.0f, 1.0f);
    transform.Owner = this;

    if (m_parent != nullptr)
    {
        transform.SetParent(m_parent);
    }

    auto& renderer = GetComponent<Assets::Components::Renderer2D>();
    renderer.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
    .TryLoadAndGetTexture(TEXTURE_FILEPATH);
}
