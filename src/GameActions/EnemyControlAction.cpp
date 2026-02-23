#include "GameActions/EnemyControlAction.h"
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"
#include <gtx/vector_angle.hpp>

void Asteroids::GameActions::EnemyControlAction::OnUpdate(float deltaTime)
{
	auto playerTransform = m_playerSpaceship->GetComponent<Assets::Components::Transform>();
	auto transform = m_spaceship->GetComponent<Assets::Components::Transform>();

	if (playerTransform != nullptr)
	{
		glm::vec2 directionToPlayer = playerTransform->LocalPosition - transform->LocalPosition;
		directionToPlayer = glm::length(directionToPlayer) > 0.0001f ? glm::normalize(directionToPlayer) : transform->Up;

		float angularDifference = -std::atan2(directionToPlayer.x * transform->Up.y -
			directionToPlayer.y * transform->Up.x, glm::dot(directionToPlayer, transform->Up));

		m_rotationValue += angularDifference * deltaTime;
		m_translationValue = 1.0f;
	}
}
