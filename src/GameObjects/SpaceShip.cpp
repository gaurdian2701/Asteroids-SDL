#include "GameObjects/SpaceShip.h"
#include "Assets/Components/Transform.h"
#include "Application/Application.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/CoreSystemsHolder.h"
#include "Core/CoreSystems/TextureResourceManager.h"
#include "Core/ECS/Systems/System.h"

constexpr inline glm::vec2 SPACESHIP_STARTING_POINT = glm::vec2(0, 0);
const inline std::string SPACESHIP_IMAGE_FILEPATH = "images/img_spaceship.png";
const inline std::string ROCKET_BOOSTER_PARTICLE_FILEPATH = "images/img_fireCircle.png";


void Asteroids::GameObjects::SpaceShip::Start()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::Renderer2D>();
	AddComponent<Assets::Components::ParticleEmitter>();

	auto& renderer = GetComponent<Assets::Components::Renderer2D>();

	renderer.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(SPACESHIP_IMAGE_FILEPATH);

	auto& transform = GetComponent<Assets::Components::Transform>();
	transform.WorldPosition = SPACESHIP_STARTING_POINT;
	transform.WorldScale = glm::vec2(50.0f);

	auto& particleEmitter = GetComponent<Assets::Components::ParticleEmitter>();

	particleEmitter.InitializeEmitter(6,
		std::forward<glm::vec2>(glm::vec2(0.0f)),
		8,
		std::forward<glm::vec2>(glm::vec2(0.05f, -0.05f)),
		0.1f,
		5.0f);

	particleEmitter.Color = SDL_FColor(255, 0, 0, 255);
	particleEmitter.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(ROCKET_BOOSTER_PARTICLE_FILEPATH);
	particleEmitter.Owner = this;


	m_aimCircleRadius = 60.0f;
}

void Asteroids::GameObjects::SpaceShip::Update(const float deltaTime)
{
	auto& t = GetComponent<Assets::Components::Transform>();
	EvaluateMovementInput(deltaTime);

	t.WorldPosition.x += m_translationVector.x * m_moveSpeed * deltaTime;
	t.WorldPosition.y += m_translationVector.y * m_moveSpeed * deltaTime;
	t.WorldRotation = m_rotationAngle;

	UpdateAimPosition();
}

void Asteroids::GameObjects::SpaceShip::UpdateAimPosition()
{
	auto& transform = GetComponent<Assets::Components::Transform>();
	float xCoordinate = transform.WorldPosition.x + m_aimCircleRadius * std::cos(glm::radians(-m_rotationAngle + 90));
	float yCoordinate = transform.WorldPosition.y + m_aimCircleRadius * std::sin(glm::radians(-m_rotationAngle + 90));

	glm::vec2 coords = Core::ECS::ConvertToScreenCoordinates(glm::vec2(xCoordinate, yCoordinate));

	SDL_SetRenderDrawColor(Application::GetCoreInstance().GetMainRenderer(), 0, 255, 0, 255);
	SDL_RenderPoint(Application::GetCoreInstance().GetMainRenderer(), coords.x, coords.y);
}

void Asteroids::GameObjects::SpaceShip::EvaluateMovementInput(const float deltaTime)
{
	m_translationVector.x = 0;
	m_translationVector.y = 0;

	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_D))
	{
		m_translationVector.x = 1;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_A))
	{
		m_translationVector.x = -1;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_W))
	{
		m_translationVector.y = 1;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_S))
	{
		m_translationVector.y = -1;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_LEFT))
	{
		m_rotationAngle -= m_rotationSpeed * deltaTime;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_RIGHT))
	{
		m_rotationAngle += m_rotationSpeed * deltaTime;
	}
}


