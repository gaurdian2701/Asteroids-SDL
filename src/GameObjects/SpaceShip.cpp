#include "GameObjects/SpaceShip.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/TextureResourceManager.h"
#include "Actions/ActionStack.h"
#include "GameActions/PlayerControlAction.h"
#include "GameActions/SpaceshipMoveAction.h"
#include "GameObjects/PlayerProjectile.h"
#include "../../include/GameObjects/PoolManager.h"

constexpr inline glm::vec2 SPACESHIP_STARTING_POINT = glm::vec2(0, 0);
const inline std::string SPACESHIP_IMAGE_FILEPATH = "images/img_spaceship.png";

void Asteroids::GameObjects::SpaceShip::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::Renderer2D>();
}

void Asteroids::GameObjects::SpaceShip::Start()
{
	GameObject::Start();

	auto renderer = GetComponent<Assets::Components::Renderer2D>();

	renderer->RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
			.TryLoadAndGetTexture(SPACESHIP_IMAGE_FILEPATH);

	auto transform = GetComponent<Assets::Components::Transform>();
	transform->LocalPosition = SPACESHIP_STARTING_POINT;
	transform->LocalScale = glm::vec2(50.0f);
	transform->Owner = this;

	m_spaceshipActionStack = new Actions::ActionStack();
	m_spaceshipActionStack->PushAction(new GameActions::PlayerControlAction());
	m_spaceshipActionStack->PushAction(new GameActions::SpaceshipMoveAction(
		dynamic_cast<GameActions::PlayerControlAction *>(m_spaceshipActionStack->GetAction<
			GameActions::PlayerControlAction>()),
		this));

	m_playerControlAction = dynamic_cast<GameActions::PlayerControlAction *>(m_spaceshipActionStack->GetAction<
		GameActions::PlayerControlAction>());
}

void Asteroids::GameObjects::SpaceShip::Update(const float deltaTime)
{
	m_spaceshipActionStack->UpdateActions(deltaTime);

	if (m_playerControlAction->GetIsShooting() && m_shootTimer >= m_timePerShot) {
		m_shootTimer = 0.0f;
		ShootBullet();
	}

	m_shootTimer += deltaTime;
}

void Asteroids::GameObjects::SpaceShip::ShootBullet()
{
	auto playerProjectile = static_cast<PlayerProjectile*>
			(PoolManager::GetInstance(GetSceneReference()).GetObjectFromPool<PlayerProjectile>());

	auto transform = GetComponent<Assets::Components::Transform>();
	playerProjectile->Initialize(transform->LocalPosition + transform->Up * m_bulletLaunchOffset,
	                             std::forward<glm::vec2>(transform->Up),
	                             transform->LocalRotation);
}
