#include "Core/ECS/Systems/ParticleSystem.h"
#include "Assets/Components/ParticleEmitter.h"
#include "vec2.hpp"
#include "Application/Application.h"
#include "Assets/Components/Transform.h"
#include "Core/GameScene.h"
#include "Core/ECS/ECSManager.h"

void Core::ECS::Systems::ParticleSystem::BeginSystem()
{
	m_maxCartesianLimits = GameScene::GetMaxCartesianLimits();
	m_minCartesianLimits = GameScene::GetMinCartesianLimits();
	// m_maxCartesianLimits.y = -m_maxCartesianLimits.y;
	// m_minCartesianLimits.y = -m_minCartesianLimits.y;

	ECSManager::GetInstance().ForEach<Assets::Components::Transform, Assets::Components::ParticleEmitter>(
		[&](const Assets::Components::Transform &transform, Assets::Components::ParticleEmitter &particleEmitter)
		{
			for (auto &particle: particleEmitter.Particles)
			{
				//Simulation
				//Set particle's initial position according to the initial velocity.
				//The positions are relative to the particle emitter's world position
				//TODO: Each particle will be in the exact same position, therefore you have to add some randomization to simulate them properly.
				particle.PreviousPosition = transform.PositionVector + particle.CurrentPosition;
				particle.CurrentPosition = particle.PreviousPosition;
				particle.CurrentPosition += particle.InitialVelocity;

				//Rendering
				RenderParticle(particleEmitter, particle);
			}
		});
}

void Core::ECS::Systems::ParticleSystem::UpdateSystem(const float deltaTime)
{
	glm::vec2 particleCurrentPosition = glm::vec2(0.0f);
	glm::vec2 particleVelocity = glm::vec2(0.0f);

	ECSManager::GetInstance().ForEach<Assets::Components::Transform, Assets::Components::ParticleEmitter>(
		[&, this](Assets::Components::Transform &transform, Assets::Components::ParticleEmitter &particleEmitter)
		{
			for (auto &particle: particleEmitter.Particles)
			{
				//Simulation
				particleCurrentPosition = particle.CurrentPosition;
				particleVelocity = particle.CurrentPosition - particle.PreviousPosition;

				//Verlet integration implicitly stores the right velocity since we are keeping track of previous frame's position as well.
				//Hence we don't need to divide by deltatime to calculate the velocity.

				particle.CurrentPosition += particleVelocity;
				particle.PreviousPosition = particleCurrentPosition;

				this->DoBoundsCheck(particle, particleVelocity);

				//Rendering
				this->RenderParticle(particleEmitter, particle);
			}
		});
}

inline void Core::ECS::Systems::ParticleSystem::DoBoundsCheck(Assets::Components::Particle& someParticle,
	const glm::vec2& someParticleVelocity)
{
	if (someParticle.CurrentPosition.x > m_maxCartesianLimits.x)
	{
		someParticle.CurrentPosition.x = this->m_maxCartesianLimits.x;
		someParticle.PreviousPosition.x = someParticle.CurrentPosition.x + someParticleVelocity.x;
	}
	else if (someParticle.CurrentPosition.x < this->m_minCartesianLimits.x)
	{
		someParticle.CurrentPosition.x = this->m_minCartesianLimits.x;
		someParticle.PreviousPosition.x = someParticle.CurrentPosition.x + someParticleVelocity.x;
	}

	if (someParticle.CurrentPosition.y < this->m_maxCartesianLimits.y)
	{
		someParticle.CurrentPosition.y = this->m_maxCartesianLimits.y;
		someParticle.PreviousPosition.y = someParticle.CurrentPosition.y + someParticleVelocity.y;
	}
	else if (someParticle.CurrentPosition.y > this->m_minCartesianLimits.y)
	{
		someParticle.CurrentPosition.y = this->m_minCartesianLimits.y;
		someParticle.PreviousPosition.y = someParticle.CurrentPosition.y + someParticleVelocity.y;
	}
}

inline void Core::ECS::Systems::ParticleSystem::RenderParticle(Assets::Components::ParticleEmitter& someParticleEmitter,
                                                               Assets::Components::Particle& someParticle)
{
	glm::vec2 screenCoordinates = ConvertToScreenCoordinates(someParticle.CurrentPosition);
	someParticleEmitter.RenderRectangle.x = screenCoordinates.x - someParticle.ParticleSize / 2;
	someParticleEmitter.RenderRectangle.y = screenCoordinates.y - someParticle.ParticleSize / 2;
	someParticleEmitter.RenderRectangle.w = someParticle.ParticleSize;
	someParticleEmitter.RenderRectangle.h = someParticle.ParticleSize;

	SDL_SetTextureColorMod(someParticleEmitter.RenderTexture,
		someParticleEmitter.Color.r,
		someParticleEmitter.Color.g,
		someParticleEmitter.Color.b);

	SDL_RenderTexture(Application::GetCoreInstance().GetMainRenderer(),
					  someParticleEmitter.RenderTexture,
					  nullptr,
					  &someParticleEmitter.RenderRectangle);
}

void Core::ECS::Systems::ParticleSystem::EndSystem()
{
}
