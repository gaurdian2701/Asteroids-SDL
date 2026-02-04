#include "Core/ECS/Systems/TransformSolverSystem.h"

#include "Assets/Components/Transform.h"
#include "Core/ECS/ECSManager.h"

void Core::ECS::Systems::TransformSolverSystem::BeginSystem()
{
	ECSManager::GetInstance().ForEach<Assets::Components::Transform>(
	[&, this](Assets::Components::Transform& transform)
	{
		this->SolveTransform(transform);
	});
}

void Core::ECS::Systems::TransformSolverSystem::UpdateSystem(const float deltaTime)
{
    ECSManager::GetInstance().ForEach<Assets::Components::Transform>(
        [&, this](Assets::Components::Transform& transform)
        {
            this->SolveTransform(transform);
        });
}

inline void Core::ECS::Systems::TransformSolverSystem::SolveTransform(Assets::Components::Transform& someTransform)
{
	if (someTransform.Parent != nullptr)
	{
		//Solve Rotation First
		someTransform.WorldRotation = someTransform.Parent->WorldRotation + someTransform.LocalRotation;

		//Then solve Scaling
		someTransform.WorldScale = someTransform.Parent->WorldScale * someTransform.LocalScale;

		//Solve Position last, you do:
		//1. Scale local position by parent scale
		glm::vec2 scaledTransform = someTransform.LocalPosition * someTransform.Parent->WorldScale;

		//2. Rotate position vector by parent rotation:
		//(xrot, yrot) = (xcost - ysint, xsint + ycost)

		float cosAngle = std::cos(someTransform.Parent->WorldRotation);
		float sinAngle = std::sin(someTransform.Parent->WorldRotation);

		glm::vec2 rotatedTransform = glm::vec2(
			scaledTransform.x * cosAngle - scaledTransform.y * sinAngle,
			scaledTransform.x * sinAngle + scaledTransform.y * cosAngle);

		//3. Add parent position to the position vector
		someTransform.WorldPosition = rotatedTransform + someTransform.Parent->WorldPosition;
	}
	else
	{
		someTransform.WorldPosition = someTransform.LocalPosition;
		someTransform.WorldRotation = someTransform.LocalRotation;
		someTransform.WorldScale = someTransform.LocalScale;
	}
}

void Core::ECS::Systems::TransformSolverSystem::EndSystem()
{

}

