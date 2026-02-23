#pragma once
#include "IControlAction.h"

namespace Scene
{
	class GameObject;
}

namespace Asteroids::GameActions
{
	class EnemyControlAction : public IControlAction
	{
	public:
		EnemyControlAction(
			Scene::GameObject *somePlayerSpaceship,
			Scene::GameObject *someSpaceship) : m_playerSpaceship(somePlayerSpaceship), m_spaceship(someSpaceship)
		{}

		~EnemyControlAction() override = default;

		void OnUpdate(float deltaTime) override;

		bool IsDone() override{ return false;}

		inline const float GetTranslationValue() override
		{
			return m_translationValue;
		}

		inline const float GetRotationValue() override
		{
			return m_rotationValue;
		}

	private:
		float m_translationValue = 0.0f;
		float m_rotationValue = 0.0f;
		Scene::GameObject *m_playerSpaceship = nullptr;
		Scene::GameObject *m_spaceship = nullptr;
	};
}
