#pragma once
#include "Scene/GameObject.h"

namespace Asteroids::GameObjects
{
    class PoolManager : public Scene::GameObject
    {
    public:
        struct PoolObject
        {
            PoolObject() = default;
            ~PoolObject() = default;

            PoolObject(bool isUsed, Scene::GameObject* someObject)
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
            Scene::GameObject* m_gameObject = nullptr;
        };

    public:
        PoolManager() = default;
        ~PoolManager() override
        {
            m_poolMap.clear();
        }

        template<typename GameObjectType>
        void RegisterPoolMap()
        {
            std::type_index gameObjectType(typeid(GameObjectType));

            if (!m_poolMap.contains(gameObjectType))
            {
                m_poolMap[gameObjectType].reserve(m_maxPoolSize);
            }
        }

        template<std::derived_from<GameObject> GameObjectType>
        GameObjectType* GetObjectFromPool()
        {
            auto& poolList = m_poolMap[std::type_index(typeid(GameObjectType))];

            std::vector<PoolObject>::iterator poolIterator = std::find_if(poolList.begin(), poolList.end(),
                [](PoolObject& poolObject)
                {
                    if (!poolObject.m_isUsed)
                    {
                        return true;
                    }
                    return false;
                });

            if (poolIterator != poolList.end() && poolIterator->m_gameObject != nullptr)
            {
                poolIterator->m_isUsed = true;
                return static_cast<GameObjectType*>(poolIterator->m_gameObject);
            }

            if (poolList.size() < m_maxPoolSize)
            {
                poolList.emplace_back(true, GetSceneReference().AddGameObject<GameObjectType>());
                return static_cast<GameObjectType*>(poolList.back().m_gameObject);
            }

            return nullptr;
        }

        template<std::derived_from<GameObject> GameObjectType>
        void ReturnObjectToPool(Scene::GameObject* gameObject)
        {
            auto& poolList = m_poolMap[std::type_index(typeid(GameObjectType))];

            std::vector<PoolObject>::iterator poolIterator = std::find_if(poolList.begin(), poolList.end(),
            [gameObject](PoolObject &poolObject)
            {
                if (poolObject.m_isUsed && poolObject.m_gameObject == gameObject)
                {
                    return true;
                }
                return false;
            });

            if (poolIterator != poolList.end())
            {
                poolIterator->m_isUsed = false;
            }
        }

    private:
        uint32_t m_maxPoolSize = 20;
        std::unordered_map<std::type_index, std::vector<PoolObject>> m_poolMap =
            std::unordered_map<std::type_index, std::vector<PoolObject>>();
    };
}
