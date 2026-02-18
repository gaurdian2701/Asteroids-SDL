#include "GameObjects/ProjectilePool.h"

#include "Core/CoreSystems/EventSystem/EventSystem.h"

void Asteroids::GameObjects::ProjectilePool::Start()
{
	m_poolList.reserve(m_maxPoolSize);
	Core::Events::EventSystem::GetInstance().RegisterEvent<ReturnProjectileToPoolEvent>(
		Core::Events::EventType::GameEvent);

	Core::Events::EventSystem::GetInstance().SubscribeToEvent<ReturnProjectileToPoolEvent>(
		Core::Events::EventType::GameEvent,
		[this](const std::any &eventData)
		{
			ReturnProjectileToPoolEvent event = std::any_cast<ReturnProjectileToPoolEvent>(eventData);
			if (event.m_projectile != nullptr)
			{
				this->ReturnProjectileToPool(event.m_projectile);
			}
		});
}

void Asteroids::GameObjects::ProjectilePool::ReturnProjectileToPool(IProjectile *projectile)
{
 	std::vector<PoolObject>::iterator poolIterator = std::find_if(m_poolList.begin(), m_poolList.end(),
	[projectile](PoolObject &poolObject)
	{
		if (poolObject.m_isUsed && poolObject.m_projectile == projectile)
		{
			return true;
		}
		return false;
	});

	if (poolIterator != m_poolList.end())
	{
		poolIterator->m_isUsed = false;
	}
}

void Asteroids::GameObjects::ProjectilePool::Update(float deltaTime)
{
}
