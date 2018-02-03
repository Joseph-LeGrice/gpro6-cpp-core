#pragma once

namespace custom_assert
{
    inline void is_true(bool x, const char* message = "custom_assert::is_true failed!")
    {
        if (!x) throw message;
    }
    
    template<typename N>
    inline void range(N x, N xMin, N xMax, const char* message = "custom_assert::in_range failed!")
    {
        is_true(x >= xMin && x < xMax, message);
    }

    template<typename N, typename A>
    inline void in_range(N x, A y, const char* message = "custom_assert::in_range failed!")
    {
        is_true(x >= 0 && x < y.size(), message);
    }

    template<typename N>
    inline void equal(N x, N y, const char* message = "custom_assert::equal failed!")
    {
        is_true(x == y, message);
    }

    template<typename N>
    inline void not_equal(N x, N y, const char* message = "custom_assert::not_equal failed!")
    {
        is_true(x != y, message);
    }

    template<typename N>
    inline void not_nan(N x)
    {
        is_true(!isnan(x));
    }

    template<typename N>
    inline void not_inf(N x)
    {
        is_true(!isinf(x));
    }
}
