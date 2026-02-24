#include "GameObjects/SpaceShipParticleEmitter.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Assets/Components/Transform.h"
#include "Core/CoreSystems/ResourceManager.h"

const inline std::string PARTICLE_TEXTURE_FILEPATH = "images/img_fireCircle.png";

void Asteroids::GameObjects::SpaceShipParticleEmitter::AddComponentsBeforeStartup()
{
	AddComponent<Assets::Components::Transform>();
	AddComponent<Assets::Components::ParticleEmitter>();
}

void Asteroids::GameObjects::SpaceShipParticleEmitter::Start()
{
	GameObject::Start();

	auto transform = GetComponent<Assets::Components::Transform>();
	transform->Owner = this;
	transform->LocalPosition = glm::vec2(0.0f, -0.5f);
	transform->LocalScale = glm::vec2(1.0f, 1.0f);
	transform->LocalRotation = glm::radians(180.0f);

	auto particleEmitter = GetComponent<Assets::Components::ParticleEmitter>();

	particleEmitter->InitializeEmitter(20,
		std::forward<glm::vec2>(glm::vec2(0.0f)),
		std::forward<glm::vec2>(glm::vec2(0.0f)),
		5.0f,
		100.0f,
		0.1f,
		5.0f);

	particleEmitter->Color = SDL_FColor(251, 115, 13, 255);
	particleEmitter->RenderTexture = GetSceneReference().GetResourceManager()
	.TryLoadAndGetTexture(PARTICLE_TEXTURE_FILEPATH);
	particleEmitter->UseOwnerDirection = true;
	particleEmitter->Owner = this;

#ifdef _DEBUG
	m_name = "Lone Emitter";
#endif
}

void Asteroids::GameObjects::SpaceShipParticleEmitter::Update(float deltaTime)
{

}

