#include "GameObjects/LoneParticleEmitter.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/TextureResourceManager.h"

const inline std::string PARTICLE_TEXTURE_FILEPATH = "images/img_fireCircle.png";

void Asteroids::GameObjects::LoneParticleEmitter::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::ParticleEmitter>();
}

void Asteroids::GameObjects::LoneParticleEmitter::Start()
{
	GameObject::Start();

	auto transform = GetComponent<Assets::Components::Transform>();
	transform->Owner = this;
	transform->LocalPosition = glm::vec2(0.0f, -0.5f);
	transform->LocalScale = glm::vec2(1.0f, 1.0f);

	auto particleEmitter = GetComponent<Assets::Components::ParticleEmitter>();

	particleEmitter->InitializeEmitter(10,
		std::forward<glm::vec2>(glm::vec2(0.0f)),
		5,
		50.0f,
		0.1f,
		5.0f);

	particleEmitter->Color = SDL_FColor(251, 115, 13, 255);
	particleEmitter->RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(PARTICLE_TEXTURE_FILEPATH);
	particleEmitter->Owner = this;
}

void Asteroids::GameObjects::LoneParticleEmitter::Update(float deltaTime)
{

}

