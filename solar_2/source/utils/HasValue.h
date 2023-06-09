#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>

namespace solar
{
    template <typename T>
    concept Pointer = std::is_pointer_v<T>;

    template <typename T>
    concept ClassWithHasValue = requires(T value) {
        {
            value.hasValue()
        } -> std::same_as<bool>;
    };

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

    template <ClassWithHasValue T> constexpr auto hasValue(const T& input) -> bool
    {
        return input.hasValue();
    }
} // namespace solar
