#include "GameObjects/PlayerProjectile.h"

#include "MiscFunctions.h"
#include "Assets/Components/Collider2D.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/ResourceManager.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "GameObjects/Asteroid.h"
#include "GameObjects/Enemyship.h"
#include "GameObjects/PoolManager.h"
#include "GameObjects/Player.h"

void Asteroids::GameObjects::PlayerProjectile::Start()
{
	ProjectileBase::Start();

	auto renderer = GetComponent<Assets::Components::Renderer2D>();
	renderer->Color = SDL_FColor(255, 0, 0, 255);

	m_player = GetSceneReference().GetGameObjectUsingType<Player>();
	m_poolManager = GetSceneReference().GetGameObjectUsingType<PoolManager>();

#ifdef _DEBUG
	m_name = "Player Projectile";
#endif
}

void Asteroids::GameObjects::PlayerProjectile::DisableProjectile()
{
	m_isActive = false;
	m_poolManager->ReturnObjectToPool<PlayerProjectile>(this);
}

void Asteroids::GameObjects::PlayerProjectile::CheckForCollisions()
{
	if (m_collider->EntityCollidedWith != Core::INVALID_ENTITY_ID &&
		m_collider->EntityCollidedWith != m_instigator->GetEntityID())
	{
		GameObject* collidedObject = GetSceneReference().GetGameObjectFromEntityID(m_collider->EntityCollidedWith);

		if (IHostile* hostile = dynamic_cast<IHostile*>(collidedObject))
		{
			Core::Events::EventSystem::GetInstance().PublishEvent<GameEvents::PlayerScoredEvent>(Core::Events::EventType::GameEvent,
				GameEvents::PlayerScoredEvent());
			hostile->OnHit();
		}

		DisableProjectile();
		m_transform->LocalPosition = MiscFunctions::GetRandomPointOnCircle(glm::vec2(0.0f),
		m_activeRadius);
	}
}



