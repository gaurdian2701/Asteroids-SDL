#include "GameObjects/ObjectPooling/ProjectileObjectPool.h"
#include "GameObjects/ProjectileBase.h"

void Asteroids::GameObjects::ProjectileObjectPool::Start()
{
    GenericObjectPool::Start();
    Core::Events::EventSystem::GetInstance().RegisterEvent<ReturnProjectileToPoolEvent>(Core::Events::EventType::GameEvent);
    Core::Events::EventSystem::GetInstance().SubscribeToEvent<ReturnProjectileToPoolEvent>(Core::Events::EventType::GameEvent,
        [this](const std::any& someEvent)
        {
            ReturnProjectileToPoolEvent returnEvent = std::any_cast<ReturnProjectileToPoolEvent>(someEvent);

            if (returnEvent.m_someProjectile != nullptr)
            {
                ReturnObjectToPool(returnEvent.m_someProjectile);
            }
        });
}
