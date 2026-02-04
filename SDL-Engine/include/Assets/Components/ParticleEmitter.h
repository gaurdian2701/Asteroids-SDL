#pragma once
#include <vector>
#include "SDL3/SDL_render.h"
#include "glm.hpp"

namespace Assets::Components
{
	struct Particle
	{
		Particle() = default;
		~Particle()
		{

		}
		//Copy Constructor
		Particle(const Particle& other)
		{
			InitialVelocity = other.InitialVelocity;
			CurrentPosition = other.CurrentPosition;
			CurrentLifeTime = other.CurrentLifeTime;
		}

		//Move Constructor
		Particle(Particle&& other) noexcept
		{
			InitialVelocity = other.InitialVelocity;
			CurrentPosition = other.CurrentPosition;
			CurrentLifeTime = other.CurrentLifeTime;
		}

		//Move Assignment operator
		Particle& operator=(Particle&& other) noexcept
		{
			if (this != &other)
			{
				InitialVelocity = other.InitialVelocity;
				CurrentPosition = other.CurrentPosition;
				CurrentLifeTime = other.CurrentLifeTime;
			}
			return *this;
		}

		bool IsDead = false;

		glm::vec2 InitialVelocity = glm::vec2(0.0f);
		glm::vec2 CurrentPosition = glm::vec2(0.0f);
		glm::vec2 PreviousPosition = glm::vec2(0.0f);

		float CurrentLifeTime = 0.0f;
		float ParticleSize = 0.0f;
	};

	struct ParticleEmitter
	{
		ParticleEmitter() = default;

		~ParticleEmitter()
		{
			RenderTexture = nullptr;
		}

		void InitializeEmitter(uint8_t numberOfParticles,
			glm::vec2&& someStartingPosition,
			glm::vec2&& someInitialVelocity,
			float someLifetime,
			float someParticleSize)
		{
			Particles.resize(numberOfParticles);

			for (auto& particle : Particles)
			{
				particle.CurrentPosition = someStartingPosition;
				particle.InitialVelocity = someInitialVelocity;
				particle.CurrentLifeTime = someLifetime;
				particle.ParticleSize = someParticleSize;
			}
		}

		//Move Constructor
		ParticleEmitter(ParticleEmitter&& other) noexcept
		{
			Friction = other.Friction;
			Bounciness = other.Bounciness;
			Color = other.Color;
			RenderRectangle = other.RenderRectangle;
			RenderTexture = other.RenderTexture;

			other.RenderTexture = nullptr;
			other.Particles.clear();
		}

		//Move Assignment operator
		ParticleEmitter& operator=(ParticleEmitter&& other) noexcept
		{
			if (this != &other)
			{
				Friction = other.Friction;
				Bounciness = other.Bounciness;
				Color = other.Color;
				RenderRectangle = other.RenderRectangle;
				RenderTexture = other.RenderTexture;

				other.RenderTexture = nullptr;
				other.Particles.clear();
			}
			return *this;
		}

		//Copy Constructor
		ParticleEmitter(const ParticleEmitter& other)
		{
			Friction = other.Friction;
			Bounciness = other.Bounciness;
			Color = other.Color;
			RenderRectangle = other.RenderRectangle;
			RenderTexture = other.RenderTexture;
		}

		float Friction = 0.0f;
		float Bounciness = 0.0f;

		SDL_FColor Color = SDL_FColor(255, 255, 255, 255);
		SDL_FRect RenderRectangle = SDL_FRect(0, 0, 5, 5);
		SDL_Texture* RenderTexture = nullptr;

		std::vector<Particle> Particles = std::vector<Particle>(5);
	};
}
