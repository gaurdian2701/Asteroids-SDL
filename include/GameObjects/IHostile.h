#pragma once

namespace Asteroids::GameObjects
{
	class IHostile
	{
	public:
		IHostile() = default;
		virtual ~IHostile() = default;

		virtual void OnHit() = 0;
	};
}