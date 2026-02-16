#pragma once
#include "Actions/IAction.h"

namespace Asteroids::GameActions
{
	class IControlAction : public Actions::IAction
	{
	public:
		IControlAction() = default;
		~IControlAction() override = default;

		void OnBegin(bool isFirstTime) override{}
		void OnUpdate(float deltaTime) override{}
		void OnEnd() override{}
		bool IsDone() override{ return false;}

		virtual inline const float GetTranslationValue() = 0;
		virtual inline const float GetRotationValue() = 0;
	};
}
