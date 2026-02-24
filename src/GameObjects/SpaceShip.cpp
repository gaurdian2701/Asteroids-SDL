#include "GameObjects/SpaceShip.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/ResourceManager.h"
#include "Actions/ActionStack.h"
#include "GameActions/PlayerControlAction.h"
#include "GameActions/SpaceshipMoveAction.h"
#include "GameObjects/PlayerProjectile.h"
#include "../../include/GameObjects/PoolManager.h"
#include "Assets/Components/Collider2D.h"
#include "Core/HelperFunctions.h"
#include "GameActions/PlayerRespawnAction.h"

constexpr inline glm::vec2 SPACESHIP_STARTING_POINT = glm::vec2(0, 0);
const inline std::string SPACESHIP_IMAGE_FILEPATH = "images/img_spaceship.png";
const inline std::string PROJECTILE_IMAGE_FILEPATH = "images/img_projectile.png";

void Asteroids::GameObjects::SpaceShip::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::Renderer2D>();
	AddComponent<Assets::Components::Collider2D>();
}

void Asteroids::GameObjects::SpaceShip::Start()
{
	GameObject::Start();

	m_maxCartesianLimits = Core::GetMaxCartesianLimits();
	m_minCartesianLimits = Core::GetMinCartesianLimits();

	auto renderer = GetComponent<Assets::Components::Renderer2D>();
	m_spaceShipTexture = GetSceneReference().GetResourceManager()
	.TryLoadAndGetTexture(SPACESHIP_IMAGE_FILEPATH);

	renderer->RenderTexture = m_spaceShipTexture;

	m_transform = GetComponent<Assets::Components::Transform>();
	m_transform->LocalPosition = SPACESHIP_STARTING_POINT;
	m_transform->LocalScale = glm::vec2(50.0f);
	m_transform->Owner = this;

	auto collider = GetComponent<Assets::Components::Collider2D>();
	collider->HalfSize = glm::vec2(m_transform->LocalScale * 0.5f);

	m_actionStack = new Actions::ActionStack();
	m_actionStack->PushAction(new GameActions::PlayerControlAction());

	m_actionStack->PushAction(new GameActions::SpaceshipMoveAction(
		200.0f, 100.0f, 5.0f, m_actionStack->GetAction<
			GameActions::PlayerControlAction>(), this));

	m_controlAction = m_actionStack->GetAction<GameActions::PlayerControlAction>();

	m_projectileTexture = GetSceneReference().GetResourceManager().TryLoadAndGetTexture(
		PROJECTILE_IMAGE_FILEPATH);

	m_poolManager = GetSceneReference().GetGameObjectUsingType<PoolManager>();
	
	m_poolManager->RegisterPoolMap<PlayerProjectile>();

#ifdef _DEBUG
	m_name = "Spaceship";
#endif
}

void Asteroids::GameObjects::SpaceShip::Update(const float deltaTime)
{
	//Get Components for current update
	m_transform = GetComponent<Assets::Components::Transform>();

	//Update Action Stack
	m_actionStack->UpdateActions(deltaTime);

	//Do Shooting
	if (m_controlAction->GetIsShooting() && m_shootTimer >= m_timePerShot)
	{
		m_shootTimer = 0.0f;
		DoShooting();
	}
	m_shootTimer += deltaTime;

	WrapPosition();
}

void Asteroids::GameObjects::SpaceShip::WrapPosition()
{
	//Check for out of bounds and wrap position if necessary
	if (m_transform->LocalPosition.x > m_maxCartesianLimits.x)
	{
		m_transform->LocalPosition.x = m_minCartesianLimits.x;
	}
	else if (m_transform->LocalPosition.x < m_minCartesianLimits.x)
	{
		m_transform->LocalPosition.x = m_maxCartesianLimits.x;
	}
	if (m_transform->LocalPosition.y > m_maxCartesianLimits.y)
	{
		m_transform->LocalPosition.y = m_minCartesianLimits.y;
	}
	else if (m_transform->LocalPosition.y < m_minCartesianLimits.y)
	{
		m_transform->LocalPosition.y = m_maxCartesianLimits.y;
	}
}


void Asteroids::GameObjects::SpaceShip::DoShooting()
{
	auto projectile = m_poolManager->GetObjectFromPool<PlayerProjectile>();

	projectile->Initialize(this, m_transform->LocalPosition + m_transform->Up * m_bulletLaunchOffset,
	                             std::forward<glm::vec2>(m_transform->Up),
	                             m_projectileTexture,
	                             m_transform->LocalRotation);
}

void Asteroids::GameObjects::SpaceShip::OnHit()
{
	m_actionStack->PushAction(new GameActions::PlayerRespawnAction(this, m_spaceShipTexture));
}


