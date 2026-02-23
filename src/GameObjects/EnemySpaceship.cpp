#include "GameObjects/EnemySpaceship.h"
#include "Assets/Components/Collider2D.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"
#include "Actions/ActionStack.h"
#include "GameActions/EnemyControlAction.h"
#include "GameObjects/SpaceShip.h"
#include "GameActions/SpaceshipMoveAction.h"
#include "GameObjects/EnemyProjectile.h"
#include "GameObjects/PoolManager.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "GameObjects/UnitManager.h"

const inline std::string ENEMY_SPACESHIP_IMAGE_FILEPATH = "images/img_enemySpaceship.png";
const inline std::string PROJECTILE_IMAGE_FILEPATH = "images/img_projectile.png";

void Asteroids::GameObjects::EnemySpaceship::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::Renderer2D>();
	AddComponent<Assets::Components::Collider2D>();
}

void Asteroids::GameObjects::EnemySpaceship::Start()
{
	GameObject::Start();

	m_player = GetSceneReference().GetGameObjectUsingType<SpaceShip>();

	m_transform = GetComponent<Assets::Components::Transform>();
	m_transform->LocalScale = glm::vec2(m_scale);

	auto renderer = GetComponent<Assets::Components::Renderer2D>();
	renderer->RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
			.TryLoadAndGetTexture(ENEMY_SPACESHIP_IMAGE_FILEPATH);

	m_projectileTexture = Core::CoreSystems::TextureResourceManager::GetInstance().TryLoadAndGetTexture(
		PROJECTILE_IMAGE_FILEPATH);

	auto collider = GetComponent<Assets::Components::Collider2D>();
	collider->HalfSize = glm::vec2(m_scale * 0.5f);

	m_actionStack = new Actions::ActionStack();
	m_actionStack->PushAction(new GameActions::EnemyControlAction(m_player, this));
	m_actionStack->PushAction(new GameActions::SpaceshipMoveAction(100.0f, 100.0f, 5.0f,
		m_actionStack->GetAction<GameActions::EnemyControlAction>(), this));

	m_poolManager = GetSceneReference().GetGameObjectUsingType<PoolManager>();
	m_poolManager->RegisterPoolMap<EnemyProjectile>();

#ifdef _DEBUG
	m_name = "EnemyShip";
#endif
}

void Asteroids::GameObjects::EnemySpaceship::Update(float deltaTime)
{
	m_transform = GetComponent<Assets::Components::Transform>();
	m_actionStack->UpdateActions(deltaTime);
	float distanceToPlayer = glm::distance(m_transform->LocalPosition,
		m_player->GetComponent<Assets::Components::Transform>()->LocalPosition);

	//Do Shooting
	if (m_shootTimer >= m_timePerShot && distanceToPlayer > m_minShootingDistance)
	{
		m_shootTimer = 0.0f;
		DoShooting();
	}

	m_shootTimer += deltaTime;
}

void Asteroids::GameObjects::EnemySpaceship::DoShooting()
{
	auto projectile = m_poolManager->GetObjectFromPool<EnemyProjectile>();

	if (projectile != nullptr)
	{
		projectile->Initialize(m_transform->LocalPosition + m_transform->Up * m_bulletLaunchOffset,
							 std::forward<glm::vec2>(m_transform->Up),
							 m_projectileTexture,
							 m_transform->LocalRotation);
	}
}

void Asteroids::GameObjects::EnemySpaceship::OnHit()
{
	Core::Events::EventSystem::GetInstance().PublishEvent<UnitManager::UnitDestroyedEvent>(
	Core::Events::EventType::GameEvent,
	m_destroyedEvent);
}



