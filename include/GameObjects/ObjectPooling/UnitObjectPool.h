#pragma once
#include "GenericObjectPool.h"

namespace Asteroids::GameObjects
{
    class UnitObjectPool : public GenericObjectPool
    {
    public:
        UnitObjectPool(uint32_t maxPoolSize) : GenericObjectPool(maxPoolSize) {}
        ~UnitObjectPool() override = default;
        void Start() override;

        struct ReturnUnitToPoolEvent
        {
            GameObject* someUnit = nullptr;
        };
    };
}
