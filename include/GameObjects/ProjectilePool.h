#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
    class IProjectile;

    class ProjectilePool : public Scene::GameObject
    {
    public:
        struct PoolObject
        {
            PoolObject() = default;
            ~PoolObject() = default;

            PoolObject(bool isUsed, IProjectile* someProjectile)
            {
                m_isUsed = isUsed;
                m_projectile = someProjectile;
            }

            //Copy Constructor
            PoolObject(const PoolObject& other)
            {
                m_isUsed = other.m_isUsed;
                m_projectile = other.m_projectile;
            }

            //Move Constructor
            PoolObject(PoolObject&& other) noexcept
            {
                if (this != &other)
                {
                    m_isUsed = other.m_isUsed;
                    m_projectile = other.m_projectile;
                }
            }

            //Copy Assignment operator
            PoolObject& operator=(const PoolObject& other)
            {
                if (this != &other)
                {
                    m_isUsed = other.m_isUsed;
                    m_projectile = other.m_projectile;
                }

                return *this;
            }

            //Move Assignment operator
            PoolObject& operator=(PoolObject&& other) noexcept
            {
                if (this != &other)
                {
                    m_isUsed = other.m_isUsed;
                    m_projectile = other.m_projectile;
                }

                return *this;
            }

            bool m_isUsed = false;
            IProjectile* m_projectile = nullptr;
        };

        ProjectilePool() = default;
        ~ProjectilePool() override = default;

        void Start() override;

        template<std::derived_from<IProjectile> ProjectileType>
        ProjectileType* GetProjectileFromPool()
        {
            std::vector<PoolObject>::iterator poolIterator = std::find_if(m_poolList.begin(), m_poolList.end(),
                [](PoolObject& projectilePoolObject)
                {
                    if (!projectilePoolObject.m_isUsed)
                    {
                        projectilePoolObject.m_isUsed = true;
                        return projectilePoolObject;
                    }
                });

            if (poolIterator != m_poolList.end())
            {
                return poolIterator->m_projectile;
            }

            m_poolList.emplace_back(true, GetSceneReference().AddGameObject<ProjectileType>());
            return m_poolList.back().m_projectile;
        }

    private:
        uint32_t m_maxPoolSize = 20;
        std::vector<PoolObject> m_poolList = std::vector<PoolObject>();
    };
}
