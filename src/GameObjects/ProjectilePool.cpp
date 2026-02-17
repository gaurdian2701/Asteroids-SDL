#include "GameObjects/ProjectilePool.h"

void Asteroids::GameObjects::ProjectilePool::Start()
{
    m_poolList.reserve(m_maxPoolSize);
}
