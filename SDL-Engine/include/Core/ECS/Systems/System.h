#pragma once
#include "vec2.hpp"
#include "Application/Application.h"
#include <bitset>
#include "Core/ECS/ECSData.h"
#include <vector>

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
		virtual void RegisterInterestedComponents() = 0;
		virtual void BeginSystem(){}
		virtual void ProcessInitializationQueue() = 0;
		virtual void UpdateSystem(const float deltaTime)
		{
			ProcessInitializationQueue();
			m_initializationQueue.clear();
		}
		virtual void EndSystem(){}

	protected:
		std::bitset<MAX_COMPONENT_TYPES> m_systemBitSet = std::bitset<MAX_COMPONENT_TYPES>();
		std::vector<uint32_t> m_initializationQueue = std::vector<uint32_t>();
		friend class ECSManager;
	};
}
