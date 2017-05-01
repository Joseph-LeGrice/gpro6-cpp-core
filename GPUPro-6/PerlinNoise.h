#pragma once

#include "glm/vec3.hpp"

namespace PerlinNoise
{
	double noise(double x, double y, double z);
	double octaveNoise(double x, double y, double z, int octaves, double persistence);
};

