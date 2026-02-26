#pragma once
#include <set>

#include "System.h"

namespace Core::ECS::Systems
{
	struct Edge
	{
	public:
		Edge() = default;
		~Edge() = default;

		Edge(std::uint32_t someEntityID, float someXCoordinate, bool isLeftEdge)
		{
			EntityOwner = someEntityID;
			xCoordinate = someXCoordinate;
			IsLeftEdge = isLeftEdge;
		}

		uint32_t EntityOwner = INVALID_ENTITY_ID;
		float xCoordinate = 0.0f;
		bool IsLeftEdge = true;
	};

	class SweepAndPrunePhysicsSystem : public System
	{
	public:
		SweepAndPrunePhysicsSystem() = default;
		~SweepAndPrunePhysicsSystem() override = default;

		void RegisterInterestedComponents() override;
		void ProcessInitializationQueue() override;
		void UpdateSystem(const float deltaTime) override;

	private:
		std::vector<Edge> m_edgesInScene = std::vector<Edge>();
		std::set<uint32_t> m_touchingEntities = std::set<uint32_t>();
	};
}
