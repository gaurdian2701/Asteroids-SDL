#include "Assets/GameObjects/TestGameObject.h"
#include "Assets/Components/Renderer2D.h"
#include "Core/CoreSystems/CoreSystemsHolder.h"

void Assets::GameObjects::TestGameObject::Start()
{
	AddComponent<Components::Transform>();
	AddComponent<Components::Renderer2D>();
	GetComponent<Components::Renderer2D>().Color = glm::vec4(0, 0, 255, 255);
}

void Assets::GameObjects::TestGameObject::Update(const float deltaTime)
{
	auto& t = GetComponent<Components::Transform>();
	EvaluateMovementInput();

	t.PositionVector.x += m_movementVector.x * m_moveSpeed * deltaTime;
	t.PositionVector.y += m_movementVector.y * m_moveSpeed * deltaTime;
}

void Assets::GameObjects::TestGameObject::EvaluateMovementInput()
{
	m_movementVector.x = 0;
	m_movementVector.y = 0;

	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_D))
	{
		m_movementVector.x = 1;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_A))
	{
		m_movementVector.x = -1;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_W))
	{
		m_movementVector.y = -1;
	}
	if (Core::MainInputSystem->CheckForKeyPress(SDL_SCANCODE_S))
	{
		m_movementVector.y = 1;
	}
}


