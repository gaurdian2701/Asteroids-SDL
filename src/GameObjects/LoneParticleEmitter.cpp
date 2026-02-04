#include "GameObjects/LoneParticleEmitter.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"

const inline std::string ROCKET_BOOSTER_PARTICLE_FILEPATH = "images/img_fireCircle.png";

void Asteroids::GameObjects::LoneParticleEmitter::Start()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::ParticleEmitter>();

	auto& transform = GetComponent<Assets::Components::Transform>();

	if (m_parent != nullptr)
	{
		transform.Parent = &m_parent->GetComponent<Assets::Components::Transform>();
		transform.LocalPosition = glm::vec2(0.0f, -20.0f);
	}

	auto& particleEmitter = GetComponent<Assets::Components::ParticleEmitter>();

	particleEmitter.InitializeEmitter(5,
		std::forward<glm::vec2>(glm::vec2(0.0f)),
		10,
		std::forward<glm::vec2>(glm::vec2(0.05f, -0.05f)),
		0.1f,
		5.0f);

	particleEmitter.Color = SDL_FColor(255, 0, 0, 255);
	particleEmitter.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(ROCKET_BOOSTER_PARTICLE_FILEPATH);
	particleEmitter.Owner = this;
}

void Asteroids::GameObjects::LoneParticleEmitter::Update(float deltaTime)
{

}

