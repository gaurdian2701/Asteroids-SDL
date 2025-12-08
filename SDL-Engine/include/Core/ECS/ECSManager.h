#pragma once
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <iostream>

#include "Components/ComponentFactory.h"
#include "SparseSet/SparseSet.h"
#include "Core/Misc.h"

namespace Core::ECS
{
    class System;

    constexpr std::size_t MAX_COMPONENT_TYPES = 32;

    class ECSManager
    {
    public:
        explicit ECSManager(const std::uint32_t maxEntities);
        ~ECSManager() = default;
        void InitializeManager();
        void UpdateManager();

        static ECSManager& GetInstance();

        std::vector<void(*)(ECSManager &, const std::uint32_t)>& GetComponentRemovalHandlesArray();

        template <typename T>
        SparseSet<T>* GetComponentPool()
        {
            return static_cast<SparseSet<T>*>(m_componentPoolMap[std::type_index(typeid(T))]);
        }

        template<typename T>
        void RegisterComponent()
        {
            m_componentFactory.RegisterComponent<T>();
            m_componentPoolMap[std::type_index(typeid(T))] = new SparseSet<T>(m_maxEntities);
        }

        template<typename T>
        void AddComponent(const std::uint32_t someEntityID)
        {
            dynamic_cast<SparseSet<T>*>(m_componentPoolMap[std::type_index(typeid(T))])
            ->AddComponentToEntity(someEntityID, std::forward<T>(m_componentFactory.CreateComponent<T>()));
        }

        template<typename T>
        void RemoveComponent(const std::uint32_t someEntityID)
        {
            dynamic_cast<SparseSet<T>*>(m_componentPoolMap[std::type_index(typeid(T))])
            ->RemoveComponentFromEntity(someEntityID);
        }

        template<typename T>
        T& GetComponent(std::uint32_t someEntityID)
        {
            auto componentPool = GetComponentPool<T>();
            return componentPool->GetDenseComponentArray()[componentPool->GetSparseEntityArray()[someEntityID]];
        }

        template<typename FirstComponentType, typename ... OtherComponentTypes>
        std::vector<std::uint32_t>& GetSmallestDenseEntityArray()
        {
            std::uint32_t smallestEntityArraySize = UINT32_MAX;
            std::type_index smallestEntityArrayTypeIndex = typeid(FirstComponentType);
            std::vector<std::uint32_t>* smallestEntityArray = &m_componentPoolMap[smallestEntityArrayTypeIndex]->GetDenseEntityArray();
            ([&]
            {
                auto& denseEntityArray = m_componentPoolMap[std::type_index(typeid(OtherComponentTypes))]->GetDenseEntityArray();
                if (const int denseEntityArraySize = denseEntityArray.size(); denseEntityArraySize < smallestEntityArraySize && denseEntityArraySize > 0)
                {
                    smallestEntityArraySize = denseEntityArraySize;
                    smallestEntityArrayTypeIndex = typeid(OtherComponentTypes);
                    smallestEntityArray = &denseEntityArray;
                }
            }(), ...);

            return *smallestEntityArray;
        }

        template<typename FirstComponentType, typename ... OtherComponentTypes>
        std::tuple<std::vector<FirstComponentType>&, std::vector<OtherComponentTypes>& ...> QueryDenseComponentArrays()
        {
            return std::forward_as_tuple(
                GetComponentPool<FirstComponentType>()->GetDenseComponentArray(),
                GetComponentPool<OtherComponentTypes>()->GetDenseComponentArray() ...);
        }

        template<typename FirstComponentType, typename ... OtherComponentTypes>
        auto QuerySparseEntityArrays()
        {
            return std::forward_as_tuple(
                GetComponentPool<FirstComponentType>()->GetSparseEntityArray(),
                GetComponentPool<OtherComponentTypes>()->GetSparseEntityArray() ...);
        }

        template<typename FirstComponentType, typename ... OtherComponentTypes, typename Functor>
        void ForEach(const Functor& someFunctor)
        {
            const auto& entities = GetSmallestDenseEntityArray<FirstComponentType, OtherComponentTypes ...>();

            for (const auto& entity : entities)
            {
                someFunctor(GetComponent<FirstComponentType>(entity), GetComponent<OtherComponentTypes>(entity) ...);
            }
        }

        [[nodiscard]] static std::size_t GenerateIndex()
        {
            static std::size_t index = 0;
            return index++;
        }

        template<typename T>
        [[nodiscard]] static bool RegisterComponentRemovalFunctionHandle(ECSManager& someManager,
            std::size_t componentTypeIndex)
        {
            someManager.GetComponentRemovalHandlesArray()[componentTypeIndex] =
                [](ECSManager& manager, const std::uint32_t someEntityID)
                {
                    manager.RemoveComponent<T>(someEntityID);
                };

            return true;
        }

        template<typename T>
        static std::size_t GetComponentTypeIndex(ECSManager& someManager)
        {
            static std::size_t componentTypeIndex = GenerateIndex();
            static bool TryGenerateComponentRemovalFunctionHandle =
                RegisterComponentRemovalFunctionHandle<T>(someManager, componentTypeIndex);

            if (componentTypeIndex == MAX_COMPONENT_TYPES)
            {
                return INVALID_INDEX;
            }
            return componentTypeIndex;
        }

        std::uint32_t GenerateEntityID();
        void FreeEntityID(const std::uint32_t entityID);

    private:
        void InitializeSystems();

    private:
        std::uint32_t m_maxEntities = 0;

        std::vector<System*> m_SystemsList;
        std::vector<std::uint32_t> m_entityFreeList;

        //TODO: Wrap sparse set in a class and have functions like HasComponent, TryGetComponent, etc.

        std::unordered_map<std::type_index, ISparseSet*> m_componentPoolMap;
        Components::ComponentFactory m_componentFactory;
        std::vector<void(*)(ECSManager&, const std::uint32_t)> m_componentRemovalHandles;
    };
}
