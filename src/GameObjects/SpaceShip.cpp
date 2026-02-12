#include "GameObjects/SpaceShip.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/TextureResourceManager.h"
#include "Core/ECS/Systems/System.h"
#include "Actions/ActionStack.h"
#include "GameActions/PlayerInputAction.h"
#include "GameActions/SpaceshipMoveAction.h"

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

	auto& renderer = GetComponent<Assets::Components::Renderer2D>();

	renderer.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(SPACESHIP_IMAGE_FILEPATH);

	auto& transform = GetComponent<Assets::Components::Transform>();
	transform.LocalPosition = SPACESHIP_STARTING_POINT;
	transform.LocalScale = glm::vec2(50.0f);
	transform.Owner = this;

	m_spaceshipActionStack = new Actions::ActionStack();
	m_spaceshipActionStack->PushAction(new GameActions::PlayerInputAction(1.0f));
	m_spaceshipActionStack->PushAction(new GameActions::SpaceshipMoveAction(
		dynamic_cast<GameActions::PlayerInputAction*>(m_spaceshipActionStack->GetAction<GameActions::PlayerInputAction>()),
		&transform, 100.0f));
}

void Asteroids::GameObjects::SpaceShip::Update(const float deltaTime)
{
	m_spaceshipActionStack->UpdateActions(deltaTime);
}


