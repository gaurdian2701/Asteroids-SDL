#include "GameObjects/SpaceShip.h"

#include "Application/Application.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/CoreSystemsHolder.h"
#include "Core/CoreSystems/TextureResourceManager.h"

constexpr inline glm::vec2 SPACESHIP_STARTING_POINT = glm::vec2(500, 500);
const inline std::string SPACESHIP_IMAGE_FILEPATH = "images/img_spaceship.png";

void Assets::GameObjects::SpaceShip::Start()
{
	AddComponent<Components::Transform>();
	AddComponent<Components::Renderer2D>();

	auto& renderer = GetComponent<Components::Renderer2D>();
	renderer.Color = SDL_FColor(255, 0, 0, 255);

	renderer.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(SPACESHIP_IMAGE_FILEPATH);

	auto& transform = GetComponent<Components::Transform>();
	transform.PositionVector = SPACESHIP_STARTING_POINT;
	transform.ScaleFactor = glm::vec2(50.0f);

	m_aimCircleRadius = std::max(transform.ScaleFactor.x, transform.ScaleFactor.y);
}

void Assets::GameObjects::SpaceShip::Update(const float deltaTime)
{
	auto& t = GetComponent<Components::Transform>();
	EvaluateMovementInput(deltaTime);

	t.PositionVector.x += m_movementVector.x * m_moveSpeed * deltaTime;
	t.PositionVector.y += m_movementVector.y * m_moveSpeed * deltaTime;
	t.Rotation = m_rotationAngle;

	UpdateAimPosition();
}

void Assets::GameObjects::SpaceShip::UpdateAimPosition()
{
	auto& transform = GetComponent<Components::Transform>();
	float xCoordinate = transform.PositionVector.x + m_aimCircleRadius * std::cos(glm::radians(m_rotationAngle - 90));
	float yCoordinate = transform.PositionVector.y + m_aimCircleRadius * std::sin(glm::radians(m_rotationAngle - 90));

	SDL_SetRenderDrawColor(Application::GetInstance().GetMainRenderer(), 0, 255, 0, 255);
	SDL_RenderPoint(Application::GetInstance().GetMainRenderer(), xCoordinate, yCoordinate);
}

void Assets::GameObjects::SpaceShip::EvaluateMovementInput(const float deltaTime)
{
	m_movementVector.x = 0;
	m_movementVector.y = 0;

	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_D))
	{
		m_movementVector.x = 1;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_A))
	{
		m_movementVector.x = -1;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_W))
	{
		m_movementVector.y = -1;
	}
	if (Core::Input::InputSystem::GetInstance().CheckForKeyPress(SDL_SCANCODE_S))
	{
		m_movementVector.y = 1;
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


