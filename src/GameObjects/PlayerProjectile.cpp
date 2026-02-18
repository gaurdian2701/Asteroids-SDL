#include "GameObjects/PlayerProjectile.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "Core/GameScene.h"
#include "GameObjects/ObjectPooling/ProjectileObjectPool.h"

const inline std::string BULLET_IMAGE_FILEPATH = "images/img_bullet.png";

void Asteroids::GameObjects::PlayerProjectile::AddComponentsBeforeStartup()
{
    AddComponent<Assets::Components::Transform>();
    AddComponent<Assets::Components::Renderer2D>();
}

void Asteroids::GameObjects::PlayerProjectile::Start()
{
    auto transform = GetComponent<Assets::Components::Transform>();
    transform->Owner = this;

    auto renderer = GetComponent<Assets::Components::Renderer2D>();
    renderer->RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance().TryLoadAndGetTexture(BULLET_IMAGE_FILEPATH);
    renderer->Color = SDL_FColor(255, 0, 0, 255);

#ifdef _DEBUG
    m_name = "Player Projectile";
#endif
}

void Asteroids::GameObjects::PlayerProjectile::Update(const float deltaTime)
{
    if (m_isActive)
    {
        auto transform = GetComponent<Assets::Components::Transform>();
        transform->LocalPosition += m_speed * deltaTime * m_movementDirection;

        if (GetSceneReference().IsGameObjectOutOfBounds(this))
        {
            Core::Events::EventSystem::GetInstance().PublishEvent<ProjectileObjectPool::ReturnProjectileToPoolEvent>(
                Core::Events::EventType::GameEvent, m_returnToPoolEvent);
            m_isActive = false;
        }
    }
}


