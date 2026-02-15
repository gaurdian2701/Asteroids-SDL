#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class LoneParticleEmitter : public Scene::GameObject
	{
	public:
		LoneParticleEmitter() = default;
		~LoneParticleEmitter() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void Update(float deltaTime) override;
	};
}
