#include "GameObjects/EnemyProjectile.h"

#include "MiscFunctions.h"
#include "GameObjects/SpaceShip.h"
#include "Assets/Components/Collider2D.h"
#include "GameObjects/PoolManager.h"

void Asteroids::GameObjects::EnemyProjectile::Start()
{
	ProjectileBase::Start();

	auto renderer = GetComponent<Assets::Components::Renderer2D>();
	renderer->Color = SDL_FColor{ 0, 255, 0, 255 };

	m_player = GetSceneReference().GetGameObjectUsingType<SpaceShip>();
	m_speed = 200.0f;
	m_poolManager = GetSceneReference().GetGameObjectUsingType<PoolManager>();
}

void Asteroids::GameObjects::EnemyProjectile::DisableProjectile()
{
	m_isActive = false;
	m_poolManager->ReturnObjectToPool<EnemyProjectile>(this);
}

void Asteroids::GameObjects::EnemyProjectile::CheckForCollisions()
{
	if (m_collider->EntityCollidedWith != Core::INVALID_ENTITY_ID)
	{
		if (m_collider->EntityCollidedWith == m_player->GetEntityID())
		{
			m_player->OnHit();
			DisableProjectile();
			m_transform->LocalPosition = MiscFunctions::GetRandomPointOnCircle(glm::vec2(0.0f),
			m_activeRadius);
		}
	}
}


