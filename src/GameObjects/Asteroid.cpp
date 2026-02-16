#include "GameObjects/Asteroid.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"

const inline std::string ASTEROID_TEXTURE_FILEPATH = "images/img_asteroid.png";

void Asteroids::GameObjects::Asteroid::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::Renderer2D>();
}

void Asteroids::GameObjects::Asteroid::Start()
{
	auto transform = GetComponent<Assets::Components::Transform>();
	transform->LocalPosition = m_startingPosition;
	transform->LocalScale = glm::vec2(m_size);
	transform->Owner = this;

	auto renderer = GetComponent<Assets::Components::Renderer2D>();
	renderer->RenderTexture = Core::CoreSystems::TextureResourceManager::
			GetInstance().TryLoadAndGetTexture(ASTEROID_TEXTURE_FILEPATH);

	std::uniform_real_distribution<float> random_distribution(-m_velocityDirectionDeviation,
	                                                          m_velocityDirectionDeviation);

	//Set starting velocity to move towards the center with a random deviation
	if (glm::length(transform->LocalPosition) > 0.0f) {
		m_initialVelocity = -glm::normalize(transform->LocalPosition) +
		                    glm::vec2(random_distribution(m_randomGenerator),
		                              random_distribution(m_randomGenerator));
	} else {
		//Don't move at all
		m_initialVelocity = glm::vec2(0.0f);
	}

	//Clamp randomized values to be within -1 to 1 range
	m_initialVelocity.x = std::clamp(m_initialVelocity.x, -1.0f, 1.0f);
	m_initialVelocity.y = std::clamp(m_initialVelocity.y, -1.0f, 1.0f);
}

void Asteroids::GameObjects::Asteroid::Update(const float deltaTime)
{
	auto transform = GetComponent<Assets::Components::Transform>();
	transform->LocalPosition +=  m_moveSpeed * deltaTime * m_initialVelocity;
	transform->LocalRotation += m_rotationSpeed * deltaTime;
}
