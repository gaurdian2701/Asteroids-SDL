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
	const auto& entities = ECSManager::GetInstance().GetSmallestDenseEntityArray<Assets::Components::Transform,
	Assets::Components::Renderer2D>();
	const auto& [denseTransformArray, denseRenderer2DArray] = m_interestedDenseComponentArrays;
	const auto& [sparseTransformArray, sparseRenderer2DArray] = m_interestedSparseArrays;

	//Systems should not directly access the sparse and dense arrays

	for (const auto& entityID : entities)
	{
		const Assets::Components::Transform& transform = denseTransformArray[sparseTransformArray[entityID]];
		Assets::Components::Renderer2D& renderer2D = denseRenderer2DArray[sparseRenderer2DArray[entityID]];

		SDL_SetRenderDrawColor(Application::GetInstance().GetMainRenderer(),
			renderer2D.Color.r, renderer2D.Color.g, renderer2D.Color.b, renderer2D.Color.a);

		renderer2D.RenderRectangle.x = transform.PositionVector.x - transform.ScaleFactor.x / 2;
		renderer2D.RenderRectangle.y = transform.PositionVector.y - transform.ScaleFactor.y / 2;
		renderer2D.RenderRectangle.w = transform.ScaleFactor.x;
		renderer2D.RenderRectangle.h = transform.ScaleFactor.y;
		SDL_RenderTexture(Application::GetInstance().GetMainRenderer(),
			renderer2D.RenderTexture, nullptr, &renderer2D.RenderRectangle);

		// SDL_RenderRect(Application::GetInstance().GetMainRenderer(), &renderer2D.RenderRectangle);
	}
}

void Core::ECS::Systems::RenderingSystem::EndSystem()
{

}

