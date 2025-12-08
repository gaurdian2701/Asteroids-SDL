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
	ECSManager::GetInstance().ForEach<Assets::Components::Transform, Assets::Components::Renderer2D>(
		[&](const Assets::Components::Transform &transform, Assets::Components::Renderer2D &renderer2D)
		{
			SDL_SetRenderDrawColor(Application::GetInstance().GetMainRenderer(),
			                       renderer2D.Color.r, renderer2D.Color.g, renderer2D.Color.b, renderer2D.Color.a);

			renderer2D.RenderRectangle.x = transform.PositionVector.x - transform.ScaleFactor.x / 2;
			renderer2D.RenderRectangle.y = transform.PositionVector.y - transform.ScaleFactor.y / 2;
			renderer2D.RenderRectangle.w = transform.ScaleFactor.x;
			renderer2D.RenderRectangle.h = transform.ScaleFactor.y;

			SDL_RenderTextureRotated(Application::GetInstance().GetMainRenderer(),
			                         renderer2D.RenderTexture, nullptr, &renderer2D.RenderRectangle,
			                         transform.Rotation, nullptr, SDL_FLIP_NONE);
		});
}

void Core::ECS::Systems::RenderingSystem::EndSystem()
{
}
