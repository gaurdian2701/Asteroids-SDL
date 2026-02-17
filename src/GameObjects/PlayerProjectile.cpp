#include "GameObjects/PlayerProjectile.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"

const inline std::string BULLET_IMAGE_FILEPATH = "images/img_bullet.png";

void Asteroids::GameObjects::PlayerProjectile::AddComponentsBeforeStartup()
{
    AddComponent<Assets::Components::Transform>();
    AddComponent<Assets::Components::Renderer2D>();
}

void Asteroids::GameObjects::PlayerProjectile::Start()
{
    auto transform = GetComponent<Assets::Components::Transform>();
    transform->LocalScale = glm::vec2(m_scale);
    transform->LocalPosition = m_startingPosition;
    transform->LocalRotation = m_startingRotation;

    auto renderer = GetComponent<Assets::Components::Renderer2D>();
    renderer->RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance().TryLoadAndGetTexture(BULLET_IMAGE_FILEPATH);
    renderer->Color = SDL_FColor(255, 0, 0, 255);

#ifdef _DEBUG
    m_name = "Player Projectile";
#endif
}

void Asteroids::GameObjects::PlayerProjectile::Update(const float deltaTime)
{
    auto transform = GetComponent<Assets::Components::Transform>();
    transform->LocalPosition += m_speed * deltaTime * m_movementDirection;
}


