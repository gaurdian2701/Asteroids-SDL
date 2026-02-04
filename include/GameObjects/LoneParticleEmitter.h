#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
	class LoneParticleEmitter : public Scene::GameObject
	{
	public:
		void Start() override;
		void Update(float deltaTime) override;
	};
}
