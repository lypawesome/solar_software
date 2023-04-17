#ifndef UTILS_H
#define UTILS_H

#define _USE_MATH_DEFINES

#include "config.h"

#include <bit>
#include <limits>





/*
    放一些常用的const常数，及常用的函数

*/
namespace solar
{



const double E = M_E;


PURE_FUNCTION constexpr auto inv_sqrt(double number) noexcept -> double
{
    static_assert(std::numeric_limits<double>::is_iec559); // (enable only
        // on IEEE 754)

    auto const y = std::bit_cast<double>(
        0x5fe6ec85e7de30da - (std::bit_cast<std::uint64_t>(number) >> 1));
    return y * (1.5 - (number * 0.5 * y * y));
}


}

#endif // UTILS_H
