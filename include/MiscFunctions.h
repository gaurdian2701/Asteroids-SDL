#pragma once
#include <corecrt_math_defines.h>
#include <random>
#include "vec2.hpp"

namespace Asteroids::MiscFunctions
{
	inline std::default_random_engine randomGenerator;

	inline glm::vec2 GetRandomPointOnCircle(glm::vec2 center, float radius)
	{
		static std::uniform_real_distribution<float> randomDistribution(0.0f, 1.0f);
		float randomPointOnUnitCircle = randomDistribution(randomGenerator) * 2 * M_PI;
		return center +
			   glm::vec2(std::cos(randomPointOnUnitCircle),
						 std::sin(randomPointOnUnitCircle)) * (radius);
	}
}
