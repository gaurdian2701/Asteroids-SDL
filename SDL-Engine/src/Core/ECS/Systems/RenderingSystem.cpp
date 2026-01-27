#include "Core/ECS/Systems/RenderingSystem.h"
#include "Application/Application.h"
#include "Core/ECS/ECSManager.h"
#include "Assets/Components/Transform.h"
#include "SDL3/SDL_render.h"

void Core::ECS::Systems::RenderingSystem::BeginSystem()
{
}

inline glm::vec2 Core::ECS::Systems::RenderingSystem::ConvertToScreenCoordinates(glm::vec2 someCartesianCoordinates)
{
	//We are given cartesian coordinates.
	//We first convert those coordinates in the range of -1 to 1.
	//First convert them to coordinates in the range of 0 to 2, then divide by 2 to bring it to 0 to 1 range
	//Then multiply those coordinates with screen width and screen height to bring it to the range of 0 to width and 0 to height

	return glm::vec2((someCartesianCoordinates.x / Application::SCREEN_WIDTH + 1) / 2 * Application::SCREEN_WIDTH,
					(1 - (someCartesianCoordinates.y / Application::SCREEN_HEIGHT + 1) / 2) * Application::SCREEN_HEIGHT);
}


void Core::ECS::Systems::RenderingSystem::UpdateSystem()
{
	ECSManager::GetInstance().ForEach<Assets::Components::Transform, Assets::Components::Renderer2D>(
		[&](const Assets::Components::Transform &transform, Assets::Components::Renderer2D &renderer2D)
		{
			SDL_SetRenderDrawColor(Application::GetCoreInstance().GetMainRenderer(),
			                       renderer2D.Color.r, renderer2D.Color.g, renderer2D.Color.b, renderer2D.Color.a);

			glm::vec2 screenCoordinates = ConvertToScreenCoordinates(transform.PositionVector);
			renderer2D.RenderRectangle.x = screenCoordinates.x - transform.ScaleFactor.x / 2;
			renderer2D.RenderRectangle.y = screenCoordinates.y - transform.ScaleFactor.y / 2;
			renderer2D.RenderRectangle.w = transform.ScaleFactor.x;
			renderer2D.RenderRectangle.h = transform.ScaleFactor.y;

			SDL_RenderTextureRotated(Application::GetCoreInstance().GetMainRenderer(),
			                         renderer2D.RenderTexture, nullptr, &renderer2D.RenderRectangle,
			                         transform.Rotation, nullptr, SDL_FLIP_NONE);
		});
}

void Core::ECS::Systems::RenderingSystem::EndSystem()
{
}
