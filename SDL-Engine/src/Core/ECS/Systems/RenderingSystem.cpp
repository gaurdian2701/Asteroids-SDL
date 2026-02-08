#include "Core/ECS/Systems/RenderingSystem.h"
#include "Application/Application.h"
#include "Core/ECS/ECSManager.h"
#include "Assets/Components/Transform.h"
#include "SDL3/SDL_render.h"
#include "Assets/Components/Renderer2D.h"

void Core::ECS::Systems::RenderingSystem::BeginSystem()
{
}

void Core::ECS::Systems::RenderingSystem::UpdateSystem(const float deltaTime)
{
	ECSManager::GetInstance().ForEach<Assets::Components::Transform, Assets::Components::Renderer2D>(
		[&](const Assets::Components::Transform &transform, Assets::Components::Renderer2D &renderer2D)
		{
			SDL_SetRenderDrawColor(Application::GetCoreInstance().GetMainRenderer(),
			                       renderer2D.Color.r, renderer2D.Color.g, renderer2D.Color.b, renderer2D.Color.a);

			glm::vec2 screenCoordinates = ConvertToScreenCoordinates(transform.WorldPosition);
			renderer2D.RenderRectangle.x = screenCoordinates.x - transform.WorldScale.x / 2;
			renderer2D.RenderRectangle.y = screenCoordinates.y - transform.WorldScale.y / 2;
			renderer2D.RenderRectangle.w = transform.WorldScale.x;
			renderer2D.RenderRectangle.h = transform.WorldScale.y;

			SDL_RenderTextureRotated(Application::GetCoreInstance().GetMainRenderer(),
			                         renderer2D.RenderTexture, nullptr, &renderer2D.RenderRectangle,
			                         -glm::degrees(transform.WorldRotation), nullptr, SDL_FLIP_NONE);
		});
}

void Core::ECS::Systems::RenderingSystem::EndSystem()
{
}
