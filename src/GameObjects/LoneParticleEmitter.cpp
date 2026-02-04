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
	transform.PositionVector = glm::vec2(10.0f, 0.0f);

	auto& emitter = GetComponent<Assets::Components::ParticleEmitter>();

	emitter.InitializeEmitter(5,
		std::forward<glm::vec2>(GetComponent<Assets::Components::Transform>().PositionVector),
		std::forward<glm::vec2>(glm::vec2(0.05f, -0.05f)),
		5.0f,
		5.0f);

	emitter.Color = SDL_FColor(255, 0, 0, 255);
	emitter.RenderTexture = Core::CoreSystems::TextureResourceManager::GetInstance()
	.TryLoadAndGetTexture(ROCKET_BOOSTER_PARTICLE_FILEPATH);
}

void Asteroids::GameObjects::LoneParticleEmitter::Update(float deltaTime)
{

}

