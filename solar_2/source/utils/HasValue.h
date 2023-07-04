#pragma once

#include <cmath>
#include <concepts>

#include <utils/Concepts.h>

namespace solar
{

    constexpr const int kUndefined = -1;

    template <std::floating_point T> constexpr auto hasValue(const T& input) -> bool
    {
        return !std::signbit(input);
    }

    template <std::signed_integral T> constexpr auto hasValue(const T& input) -> bool
    {
        return input > kUndefined;
    }

    template <Pointer T> constexpr auto hasValue(const T& input) -> bool { return (!!input); }

    template <ClassWithEmpty T> auto hasValue(const T& input) -> bool { return !input.empty(); }

    template <ClassWithHasValue T> auto hasValue(const T& input) -> bool
    {
        return input.hasValue();
    }

    template <typename T> auto hasValue(const T&) -> bool { return true; }
} // namespace solar
