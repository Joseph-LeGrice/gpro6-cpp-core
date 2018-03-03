#pragma once
#include <stdexcept>

namespace custom_assert
{
	struct custom_assert_error
	{
		const char* m_message;
		custom_assert_error(const char* message) : m_message(message) { }
	};

	__forceinline void is_true(const bool& x)
    {
		if (!x) throw custom_assert_error("Assertion Failed");
    }
    
    template<typename N>
    __forceinline void range(const N& x, const N& xMin, const N& xMax)
    {
        is_true(x >= xMin && x < xMax);
    }

    template<typename N, typename A>
    __forceinline void in_range(const N& x, const A& y)
    {
        is_true(x >= 0 && x < y.size());
    }

    template<typename N>
    __forceinline void equal(const N& x, const N& y)
    {
        is_true(x == y);
    }

    template<typename N>
    __forceinline void not_equal(const N& x, const N& y)
    {
        is_true(x != y);
    }

    template<typename N>
    __forceinline void not_nan(const N& x)
    {
        is_true(!isnan(x));
    }

    template<typename N>
    __forceinline void not_inf(const N& x)
    {
        is_true(!isinf(x));
    }
}
