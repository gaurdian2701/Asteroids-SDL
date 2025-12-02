#pragma once
#include "EventSystem/EventSystem.h"
#include "InputSystem/InputSystem.h"

namespace Core
{
	inline auto MainEventSystem = new Events::EventSystem();
	inline auto MainInputSystem = new Input::InputSystem();

	inline std::vector<CoreSystem*> MakeCoreSystemsVector()
	{
		return std::vector<CoreSystem*>{
		MainEventSystem,
		MainInputSystem};
	}

	inline std::vector<CoreSystem*> GetCoreSystems()
	{
		static std::vector<CoreSystem*> coreSystems = MakeCoreSystemsVector();
		return coreSystems;
	}
}
