#pragma once
#include <stdexcept>

namespace custom_assert
{
	struct custom_assert_error
	{
		const char* m_message;
		custom_assert_error(const char* message) : m_message(message) { }
	};

	__forceinline void is_true(const bool& x, const char* msg = "Assertion Failed!")
    {
		if (!x) throw custom_assert_error(msg);
    }
    
    template<typename N>
    __forceinline void range(const N& x, const N& xMin, const N& xMax, const char* msg = "Assertion Failed!")
    {
        is_true(x >= xMin && x < xMax, msg);
    }

    template<typename N, typename A>
    __forceinline void in_range(const N& x, const A& y, const char* msg = "Assertion Failed!")
    {
        is_true(x >= 0 && x < y.size(), msg);
    }

    template<typename N>
    __forceinline void equal(const N& x, const N& y, const char* msg = "Assertion Failed!")
    {
        is_true(x == y, msg);
    }

    template<typename N>
    __forceinline void not_equal(const N& x, const N& y, const char* msg = "Assertion Failed!")
    {
        is_true(x != y, msg);
    }

    template<typename N>
    __forceinline void not_nan(const N& x, const char* msg = "Assertion Failed!")
    {
        is_true(!isnan(x), msg);
    }

    template<typename N>
    __forceinline void not_inf(const N& x, const char* msg = "Assertion Failed!")
    {
        is_true(!isinf(x), msg);
    }
}
