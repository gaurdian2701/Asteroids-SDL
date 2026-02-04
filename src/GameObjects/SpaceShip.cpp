#include "GameObjects/SpaceShip.h"
#include "Assets/Components/Transform.h"
#include "Application/Application.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/CoreSystemsHolder.h"
#include "Core/CoreSystems/TextureResourceManager.h"
#include "Core/ECS/Systems/System.h"

constexpr inline glm::vec2 SPACESHIP_STARTING_POINT = glm::vec2(0, 0);
const inline std::string SPACESHIP_IMAGE_FILEPATH = "images/img_spaceship.png";

void Asteroids::GameObjects::SpaceShip::Start()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::Renderer2D>();

	auto& renderer = GetComponent<Assets::Components::Renderer2D>();

	renderer.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(SPACESHIP_IMAGE_FILEPATH);

	auto& transform = GetComponent<Assets::Components::Transform>();
	transform.PositionVector = SPACESHIP_STARTING_POINT;
	transform.ScaleFactor = glm::vec2(50.0f);

	m_aimCircleRadius = 60.0f;
}

void Asteroids::GameObjects::SpaceShip::Update(const float deltaTime)
{
	auto& t = GetComponent<Assets::Components::Transform>();
	EvaluateMovementInput(deltaTime);

	t.PositionVector.x += m_translationVector.x * m_moveSpeed * deltaTime;
	t.PositionVector.y += m_translationVector.y * m_moveSpeed * deltaTime;
	t.Rotation = m_rotationAngle;

	UpdateAimPosition();
}

void Asteroids::GameObjects::SpaceShip::UpdateAimPosition()
{
	auto& transform = GetComponent<Assets::Components::Transform>();
	float xCoordinate = transform.PositionVector.x + m_aimCircleRadius * std::cos(glm::radians(-m_rotationAngle + 90));
	float yCoordinate = transform.PositionVector.y + m_aimCircleRadius * std::sin(glm::radians(-m_rotationAngle + 90));

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


