#pragma once

namespace Core::ECS
{
	class System
	{
	public:
		System() = default;
		virtual ~System() = default;
		virtual void BeginSystem() = 0;
		virtual void UpdateSystem() = 0;
		virtual void EndSystem() = 0;
	};
}