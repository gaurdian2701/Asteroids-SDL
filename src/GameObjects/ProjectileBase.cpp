#include "GameObjects/ProjectileBase.h"
#include "Assets/Components/Collider2D.h"
#include "Assets/Components/Renderer2D.h"

void Asteroids::GameObjects::ProjectileBase::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::Renderer2D>();
	AddComponent<Assets::Components::Collider2D>();
}

void Asteroids::GameObjects::ProjectileBase::Start()
{
	auto transform = GetComponent<Assets::Components::Transform>();
	transform->Owner = this;

	auto collider = GetComponent<Assets::Components::Collider2D>();
	collider->HalfSize = glm::vec2(transform->LocalScale * 0.3f);
}

void Asteroids::GameObjects::ProjectileBase::Update(const float deltaTime)
{
	m_transform = GetComponent<Assets::Components::Transform>();
	m_collider = GetComponent<Assets::Components::Collider2D>();

	m_transform->LocalPosition += m_speed * deltaTime * m_movementDirection;

	if (m_transform->LocalPosition.x * m_transform->LocalPosition.x +
		m_transform->LocalPosition.y * m_transform->LocalPosition.y > m_activeRadius * m_activeRadius)
	{
		DisableProjectile();
	}
	CheckForCollisions();
}

