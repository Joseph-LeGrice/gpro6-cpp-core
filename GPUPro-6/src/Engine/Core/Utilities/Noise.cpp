#include "stdafx.h"
#include "Noise.h"

#include <math.h>

namespace Noise
{
    float Value(Vector3 point, float frequency)
    {
        point *= frequency;
        return static_cast<float>(static_cast<int>(point.X) % 2);
    }
}
