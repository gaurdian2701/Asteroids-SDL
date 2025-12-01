#include "Assets/GameObjects/TestGameObject.h"

void Assets::GameObjects::TestGameObject::Start()
{
	AddComponent<Components::Transform>();
}

void Assets::GameObjects::TestGameObject::Update(const float deltaTime)
{
	auto& t = GetComponent<Components::Transform>();
	t.PositionVector.x += m_moveSpeed * deltaTime;
	t.PositionVector.y += m_moveSpeed * deltaTime;
}

