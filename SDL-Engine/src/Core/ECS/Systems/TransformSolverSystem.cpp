#include "Core/ECS/Systems/TransformSolverSystem.h"

#include "Assets/Components/Transform.h"
#include "Core/ECS/ECSManager.h"

void Core::ECS::Systems::TransformSolverSystem::BeginSystem()
{

}

void Core::ECS::Systems::TransformSolverSystem::UpdateSystem(const float deltaTime)
{
    ECSManager::GetInstance().ForEach<Assets::Components::Transform>(
        [&](Assets::Components::Transform& transform)
        {
            if (transform.Parent != nullptr)
            {
                //Solve Rotation First
                transform.WorldRotation = transform.Parent->WorldRotation + transform.LocalRotation;

                //Then solve Scaling
                transform.WorldScale = transform.Parent->WorldScale * transform.LocalScale;

                glm::vec2 solvedTransform(0.0f);

                //Solve Position last, you do:
                //1. Scale local position by parent scale
                solvedTransform = transform.LocalPosition * transform.Parent->WorldScale;

                //2. Rotate position vector by parent rotation:
                //(xrot, yrot) = (xcost - ysint, xsint + ycost)
                solvedTransform = glm::vec2(
                    transform.LocalPosition.x * std::cos(transform.Parent->WorldRotation) - transform.LocalPosition.y * std::sin(transform.Parent->WorldRotation),
                    transform.LocalPosition.x * std::sin(transform.Parent->WorldRotation) + transform.LocalPosition.y * std::cos(transform.Parent->WorldRotation));

                //3. Add parent position to the position vector
                transform.WorldPosition = solvedTransform + transform.Parent->WorldPosition;
            }
            else
            {
                transform.LocalPosition = transform.WorldPosition;
                transform.LocalScale = transform.WorldScale;
                transform.LocalRotation = transform.WorldRotation;
            }
        });
}

void Core::ECS::Systems::TransformSolverSystem::EndSystem()
{

}

