#include "GameObjects/Asteroid.h"
#include "Assets/Components/Collider2D.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Assets/Components/ParticleEmitter.h"
#include "Core/CoreSystems/ResourceManager.h"
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "GameObjects/SpaceShip.h"
#include "gtx/rotate_vector.hpp"

const inline std::string ASTEROID_TEXTURE_FILEPATH = "images/img_asteroid.png";
const inline std::string PARTICLE_TEXTURE_FILEPATH = "images/img_fireCircle.png";

void Asteroids::GameObjects::Asteroid::AddComponentsBeforeStartup()
{
    AddComponent<Assets::Components::Transform>();
    AddComponent<Assets::Components::Renderer2D>();
    AddComponent<Assets::Components::Collider2D>();
    AddComponent<Assets::Components::ParticleEmitter>();
}

void Asteroids::GameObjects::Asteroid::Start()
{
    auto transform = GetComponent<Assets::Components::Transform>();
    transform->LocalPosition = m_startingPosition;
    transform->LocalScale = glm::vec2(m_startingScale);
    transform->Owner = this;

    auto renderer = GetComponent<Assets::Components::Renderer2D>();
    renderer->RenderTexture = GetSceneReference().GetResourceManager().TryLoadAndGetTexture(ASTEROID_TEXTURE_FILEPATH);

    auto collider = GetComponent<Assets::Components::Collider2D>();
    collider->HalfSize = glm::vec2(m_startingScale * 0.5f);

    auto particleEmitter = GetComponent<Assets::Components::ParticleEmitter>();
    particleEmitter->InitializeEmitter(30,
                                       std::forward<glm::vec2>(glm::vec2(0.0f)),
                                       std::forward<glm::vec2>(glm::vec2(0.0f)),
                                       20.0f,
                                       m_particleSpeed,
                                       0.15f,
                                       5.0f);

    particleEmitter->RenderTexture = GetSceneReference().GetResourceManager()
        .GetTexture(PARTICLE_TEXTURE_FILEPATH);
    particleEmitter->Color = SDL_FColor{255, 200, 120, 255};

    m_player = GetSceneReference().GetGameObjectUsingType<SpaceShip>();
    ResetVelocity();

#ifdef _DEBUG
    m_name = "Asteroid";
#endif
}

void Asteroids::GameObjects::Asteroid::InitializeAsteroid(glm::vec2&& someStartingPosition,
                                                          glm::vec2&& someMovementDirection, float someScale,
                                                          float someAngularDeviationInDegrees, float someActiveRadius)
{
    m_startingPosition = someStartingPosition;
    m_movementDirection = someMovementDirection;
    m_startingScale = someScale;
    m_velocityAngularDeviationInDegrees = someAngularDeviationInDegrees;
    m_activeRadius = someActiveRadius;
}

void Asteroids::GameObjects::Asteroid::ResetVelocity()
{
    auto transform = GetComponent<Assets::Components::Transform>();

    transform->LocalPosition = m_startingPosition;
    transform->LocalScale = glm::vec2(m_startingScale);

    std::uniform_real_distribution<float> random_distribution(-m_velocityAngularDeviationInDegrees,
                                                              m_velocityAngularDeviationInDegrees);

    //Set starting velocity to move towards the center with a random deviation
    if (glm::length(transform->LocalPosition) > 0.0f)
    {
        float angularDeviationInRadians = glm::radians(random_distribution(m_randomGenerator));
        m_movementDirection = glm::rotate(m_movementDirection, angularDeviationInRadians);
    }
    else
    {
        //Don't move at all
        m_movementDirection = glm::vec2(0.0f);
    }

    //Clamp randomized values to be within -1 to 1 range
    m_movementDirection.x = std::clamp(m_movementDirection.x, -1.0f, 1.0f);
    m_movementDirection.y = std::clamp(m_movementDirection.y, -1.0f, 1.0f);

    auto particleEmitter = GetComponent<Assets::Components::ParticleEmitter>();
    particleEmitter->Direction = -m_movementDirection;
}

void Asteroids::GameObjects::Asteroid::Update(const float deltaTime)
{
    auto transform = GetComponent<Assets::Components::Transform>();
    transform->LocalPosition += m_moveSpeed * deltaTime * m_movementDirection;
    transform->LocalRotation += m_rotationSpeed * deltaTime;

    m_collider = GetComponent<Assets::Components::Collider2D>();

    //Is the asteroid outside of the circle?
    if (transform->LocalPosition.x * transform->LocalPosition.x + transform->LocalPosition.y * transform->LocalPosition.
        y > m_activeRadius
        * m_activeRadius)
    {
        Core::Events::EventSystem::GetInstance().PublishEvent<UnitManager::UnitLeftActiveRadiusEvent>(
            Core::Events::EventType::GameEvent,
            m_onLeftActiveRadiusEvent);
    }

    CheckForCollisions();
}

void Asteroids::GameObjects::Asteroid::CheckForCollisions()
{
    if (m_collider->EntityCollidedWith != Core::INVALID_ENTITY_ID)
    {
        if (m_player != nullptr && m_player->GetEntityID() == m_collider->EntityCollidedWith)
        {
            m_player->OnHit();
            OnHit();
        }
    }
}

void Asteroids::GameObjects::Asteroid::OnHit()
{
    Core::Events::EventSystem::GetInstance().PublishEvent<UnitManager::UnitDestroyedEvent>(
        Core::Events::EventType::GameEvent,
        m_onDestroyedEvent);
}
