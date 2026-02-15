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
}

void Asteroids::GameObjects::Asteroid::Update(const float deltaTime)
{
}

