#include "GameObjects/ObjectPooling/UnitObjectPool.h"

void Asteroids::GameObjects::UnitObjectPool::Start()
{
    GenericObjectPool::Start();
    Core::Events::EventSystem::GetInstance().RegisterEvent<ReturnUnitToPoolEvent>(Core::Events::EventType::GameEvent);
    Core::Events::EventSystem::GetInstance().SubscribeToEvent<ReturnUnitToPoolEvent>(Core::Events::EventType::GameEvent,
        [this](const std::any& someEvent)
        {
            ReturnUnitToPoolEvent returnEvent = std::any_cast<ReturnUnitToPoolEvent>(someEvent);

            if (returnEvent.someUnit != nullptr)
            {
                ReturnObjectToPool(returnEvent.someUnit);
            }
        });
}
