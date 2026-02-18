#pragma once
#include "Core/CoreSystems/EventSystem/EventSystem.h"
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
    class GenericObjectPool : public Scene::GameObject
    {
    public:
        struct PoolObject
        {
            PoolObject() = default;
            ~PoolObject() = default;

            PoolObject(bool isUsed, GameObject* someObject)
            {
                m_isUsed = isUsed;
                m_gameObject = someObject;
            }

            //Copy Constructor
            PoolObject(const PoolObject& other)
            {
                m_isUsed = other.m_isUsed;
                m_gameObject = other.m_gameObject;
            }

            //Move Constructor
            PoolObject(PoolObject&& other) noexcept
            {
                if (this != &other)
                {
                    m_isUsed = other.m_isUsed;
                    m_gameObject = other.m_gameObject;
                }
            }

            //Copy Assignment operator
            PoolObject& operator=(const PoolObject& other)
            {
                if (this != &other)
                {
                    m_isUsed = other.m_isUsed;
                    m_gameObject = other.m_gameObject;
                }
                return *this;
            }

            //Move Assignment operator
            PoolObject& operator=(PoolObject&& other) noexcept
            {
                if (this != &other)
                {
                    m_isUsed = other.m_isUsed;
                    m_gameObject = other.m_gameObject;
                }
                return *this;
            }

            bool m_isUsed = false;
            GameObject* m_gameObject = nullptr;
        };

    public:
        explicit GenericObjectPool(uint32_t somePoolSize) : m_maxPoolSize(somePoolSize) {};
        ~GenericObjectPool() override = default;

        void Start() override
        {
            m_poolList.reserve(m_maxPoolSize);
        }

        template<std::derived_from<GameObject> GameObjectType>
        GameObject* GetObjectFromPool()
        {
            std::vector<PoolObject>::iterator poolIterator = std::find_if(m_poolList.begin(), m_poolList.end(),
                [](PoolObject& poolObject)
                {
                    if (!poolObject.m_isUsed)
                    {
                        return true;
                    }
                    return false;
                });

            if (poolIterator != m_poolList.end() && poolIterator->m_gameObject != nullptr)
            {
                poolIterator->m_isUsed = true;
                return poolIterator->m_gameObject;
            }

            m_poolList.emplace_back(true, GetSceneReference().AddGameObject<GameObjectType>());
            return m_poolList.back().m_gameObject;
        }

        void ReturnObjectToPool(GameObject* gameObject)
        {
            std::vector<PoolObject>::iterator poolIterator = std::find_if(m_poolList.begin(), m_poolList.end(),
            [gameObject](PoolObject& poolObject)
            {
                if (poolObject.m_isUsed && poolObject.m_gameObject == gameObject)
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

    private:
        uint32_t m_maxPoolSize = 0;
        std::vector<PoolObject> m_poolList = std::vector<PoolObject>();
    };
}
