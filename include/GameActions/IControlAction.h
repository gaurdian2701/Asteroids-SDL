#pragma once
#include "Actions/IAction.h"

namespace Asteroids::GameActions
{
	class IControlAction : public Actions::IAction
	{
	public:
		IControlAction() = default;
		~IControlAction() override = default;

		bool IsDone() override{ return false;}

		virtual inline const float GetTranslationValue() = 0;
		virtual inline const float GetRotationValue() = 0;
	};
}
