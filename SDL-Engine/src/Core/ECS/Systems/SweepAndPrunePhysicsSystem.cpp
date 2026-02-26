#include "Core/ECS/Systems/SweepAndPrunePhysicsSystem.h"
#include "Assets/Components/Collider2D.h"
#include "Assets/Components/Transform.h"

void Core::ECS::Systems::SweepAndPrunePhysicsSystem::RegisterInterestedComponents()
{
	ECSManager::GetInstance().RegisterInterestedComponentsForSystem<Assets::Components::Transform,
		Assets::Components::Collider2D>(this);
}

void Core::ECS::Systems::SweepAndPrunePhysicsSystem::ProcessInitializationQueue()
{
 	ECSManager::GetInstance().ForEachUsingEntitiesWithEntityID<Assets::Components::Transform,
		Assets::Components::Collider2D>
	(m_initializationQueue,
	 [&](std::uint32_t entityID, const Assets::Components::Transform *transform,
	     Assets::Components::Collider2D *collider)
	 {
		 m_edgesInScene.push_back(Edge(
			 entityID,
			 transform->WorldPosition.x - collider->HalfSize.x,
			 true));

		 m_edgesInScene.push_back(Edge(
			 entityID,
			 transform->WorldPosition.x + collider->HalfSize.x,
			 false));

			collider->EntityCollidedWith = INVALID_ENTITY_ID;
	 });
}

void Core::ECS::Systems::SweepAndPrunePhysicsSystem::UpdateSystem(const float deltaTime)
{
	m_edgesInScene.clear();
	m_touchingEntities.clear();

	System::UpdateSystem(deltaTime);

	//Construct/Update the edge list
	ECSManager::GetInstance().ForEachUsingComponentsWithEntityID<Assets::Components::Transform, Assets::Components::Collider2D>(
		[&](std::uint32_t entityID, const Assets::Components::Transform* transform,
			Assets::Components::Collider2D* collider)
		{
			m_edgesInScene.push_back(Edge(
				entityID,
				transform->WorldPosition.x - collider->HalfSize.x,
				true));

			m_edgesInScene.push_back(Edge(
				entityID,
				transform->WorldPosition.x + collider->HalfSize.x,
				false));

			collider->EntityCollidedWith = INVALID_ENTITY_ID;
		});

	//Sort the edges list according to the X coordinates
	std::sort(m_edgesInScene.begin(), m_edgesInScene.end(),
	          [&](const Edge &a, const Edge &b)
	          {
	          	if (a.xCoordinate < b.xCoordinate)
	          		return true;

				  if (a.xCoordinate > b.xCoordinate)
				  	return false;

				  return a.IsLeftEdge && !b.IsLeftEdge;
	          });

	glm::vec2 mainEntityPosition = glm::vec2(0.0f);
	glm::vec2 mainEntityHalfExtents = glm::vec2(0.0f);
	glm::vec2 otherEntityPosition = glm::vec2(0.0f);
	glm::vec2 otherEntityHalfExtents = glm::vec2(0.0f);

	for (const auto &edge: m_edgesInScene)
	{
		//If left edge,
		if (edge.IsLeftEdge)
		{
			mainEntityPosition = ECSManager::GetInstance().GetComponent<
				Assets::Components::Transform>(edge.EntityOwner)->WorldPosition;
			mainEntityHalfExtents = ECSManager::GetInstance().GetComponent<
				Assets::Components::Collider2D>(edge.EntityOwner)->HalfSize;

			//Do Overlap check against every other entity in the touching set
			for (const auto entity: m_touchingEntities)
			{
				otherEntityPosition = ECSManager::GetInstance().GetComponent<Assets::Components::Transform>(entity)
						->WorldPosition;
				otherEntityHalfExtents = ECSManager::GetInstance().GetComponent<Assets::Components::Collider2D>(entity)
						->HalfSize;

				if (std::abs(mainEntityPosition.y - otherEntityPosition.y)
				    < mainEntityHalfExtents.y + otherEntityHalfExtents.y)
				{
					ECSManager::GetInstance().GetComponent<Assets::Components::Collider2D>(entity)->EntityCollidedWith =
							edge.EntityOwner;
					ECSManager::GetInstance().GetComponent<Assets::Components::Collider2D>(edge.EntityOwner)->
							EntityCollidedWith = entity;
				}
			}
			//Add it to the touching set
			m_touchingEntities.insert(edge.EntityOwner);
		}
		//Remove from the touching set if right edge
		else
		{
			m_touchingEntities.erase(edge.EntityOwner);
		}
	}

}
