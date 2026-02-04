#pragma once
#include "vec2.hpp"
#include "Application/Application.h"

namespace Core::ECS
{
	static inline glm::vec2 ConvertToScreenCoordinates(glm::vec2 someCartesianCoordinates)
	{
		return glm::vec2(someCartesianCoordinates.x + Application::SCREEN_WIDTH / 2,
			Application::SCREEN_HEIGHT/2 - someCartesianCoordinates.y);
	}

	class System
	{
	public:
		System() = default;
		virtual ~System() = default;
		virtual void BeginSystem() = 0;
		virtual void UpdateSystem(const float deltaTime) = 0;
		virtual void EndSystem() = 0;
	};
}
