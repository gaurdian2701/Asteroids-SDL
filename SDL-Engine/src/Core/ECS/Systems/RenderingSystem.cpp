#include "Core/ECS/Systems/RenderingSystem.h"

#include "Application/Application.h"
#include "Core/ECS/ECSManager.h"
#include "Assets/Components/Transform.h"

#include "SDL3/SDL_render.h"

void Core::ECS::Systems::RenderingSystem::BeginSystem()
{
}

void Core::ECS::Systems::RenderingSystem::UpdateSystem()
{
	auto& entities = ECSManager::GetInstance()->GetSmallestEntityArray<Assets::Components::Transform>();

	for (auto& entity : entities)
	{
		auto& [transformComponentArray, renderer2DArray] = m_interestedComponents;
		SDL_SetRenderDrawColor(Application::GetInstance()->GetMainRenderer(),
			255, 0, 0, 255);
		SDL_RenderPoint(Application::GetInstance()->GetMainRenderer(), transformComponentArray[entity].PositionVector.x,
			transformComponentArray[entity].PositionVector.y);
	}
}

void Core::ECS::Systems::RenderingSystem::EndSystem()
{

}

