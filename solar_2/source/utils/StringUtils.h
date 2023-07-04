#pragma once

#include <charconv>
#include <concepts>
#include <cstdint>
#include <memory_resource>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "config.h"
#include "utils/Concepts.h"

namespace solar
{
    namespace internal
    {
        static std::array<std::byte, 10000> buf{};
        static std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
        static std::pmr::synchronized_pool_resource synchronized_pool{&pool};
    } // namespace internal

    template <Number T> PURE_FUNCTION auto toString(const T& value) -> std::string
    {
        std::pmr::vector<char> str(100, &internal::synchronized_pool);
        if (auto [ptr, ec] = std::to_chars(str.data(), str.data() + str.size(), value);
            ec == std::errc())
        {
            return {str.data(), ptr};
        }
        else
        {
            throw std::make_error_code(ec).message();
        }
    }

    template <StringLike T> auto toString(const T& value) -> std::string { return value; }

    template <Enum T> auto toString(const T& value) -> std::string
    {
        return ::solar::toString(static_cast<int>(value));
    }

    template <ClassWithToString T> auto toString(const T& value) -> std::string
    {
        return value.toString();
    }

    template <std::integral T> PURE_FUNCTION auto fromString(const std::string& input) -> T
    {
        T result{};
        if (auto [ptr, ec] = std::from_chars(input.data(), input.data() + input.size(), result);
            ec == std::errc())
        {
            return result;
        }
        else
        {
            throw std::make_error_code(ec).message();
        }
    }

    // LibC++ does not support floating-point version of std::from_chars

    template <std::floating_point T> PURE_FUNCTION auto fromString(const std::string& input) -> T
    {
        if constexpr (std::is_same_v<float, T>)
        {
            return std::stof(input);
        }
        if constexpr (std::is_same_v<double, T>)
        {
            return std::stod(input);
        }
        if constexpr (std::is_same_v<long double, T>)
        {
            return std::stold(input);
        }
        return T{};
    }

    template <StringLike T> constexpr auto fromString(const std::string& input) -> T
    {
        return T(input);
    }

    template <Enum T> auto fromString(const std::string& input) -> T
    {
        return T(::solar::fromString<int>(input));
    }

    template <ClassWithFromString T> auto fromString(const std::string& input) -> T
    {
        return T::fromString(input);
    }
} // namespace solar
