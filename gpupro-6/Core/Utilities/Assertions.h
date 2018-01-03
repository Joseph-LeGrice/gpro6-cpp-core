#pragma once
#include "assert.h"

#define assertion(x) assert(x)
#define assertion_range(x, xMin, xMax) assertion(x >= xMin && x < xMax)
#define assertion_equal(x, y) assertion(x == y)
#define assertion_not_equal(x, y) assertion(x != y)