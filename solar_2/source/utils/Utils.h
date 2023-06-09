#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include "utils/config.h"

#include <array>
#include <bit>
#include <charconv>
#include <concepts>
#include <cstdint>
#include <limits>
#include <memory_resource>
#include <string>
#include <type_traits>
#include <vector>

/*
    放一些常用的const常数，及常用的函数

*/
namespace solar
{
    namespace internal
    {
        static std::array<std::byte, 10000> buf{};
        static std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
        static std::pmr::synchronized_pool_resource synchronized_pool{&pool};
    } // namespace internal

    template <typename T>
    concept ClassWithToString = requires(T value) {
        {
            value.toString()
        } -> std::same_as<std::string>;
    };

    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    PURE_FUNCTION constexpr auto inv_sqrt(double number) noexcept -> double
    {
        // (enable only on IEEE 754)
        static_assert(std::numeric_limits<double>::is_iec559);

        auto const y =
            std::bit_cast<double>(0x5fe6ec85e7de30da - (std::bit_cast<std::uint64_t>(number) >> 1));
        return y * (1.5 - (number * 0.5 * y * y));
    }

    template <Number T> PURE_FUNCTION auto toString(const T& value) -> std::string
    {
        std::pmr::vector<char> str(100, &internal::synchronized_pool);
        if (auto [ptr, ec] =
                std::to_chars(str.data(), str.data() + str.size(), value, std::chars_format::fixed);
            ec == std::errc())
        {
            return {str.data(), ptr};
        }
        else
        {
            throw std::make_error_code(ec).message();
        }
    }

    template <ClassWithToString T> auto toString(const T& value) -> std::string
    {
        return value.toString();
    }
} // namespace solar

#endif // UTILS_H
