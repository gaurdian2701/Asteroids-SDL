#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class SpaceShipParticleEmitter : public Scene::GameObject
	{
	public:
		SpaceShipParticleEmitter() = default;
		~SpaceShipParticleEmitter() override = default;

		void AddComponentsBeforeStartup() override;
		void Start() override;
		void Update(float deltaTime) override;
	};
}
