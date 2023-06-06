#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#define _USE_MATH_DEFINES

#include "config.h"
#include <cmath>
#include <bit>
#include <limits>

#include "utils/Vec3.h"
#include "utils/Vec2.h"
#include "utils/Para.h"





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

// 把一个double转化为string，并且要求不能有尾0
static std::string double2String(double x)
{
    std::string ret = std::to_string(x);
    bool has_dot = false;
    int id = ret.size()-1;
    while(id)
    {
        if(ret[id]=='.'){
            has_dot = true;
            id--;
            break;
        }
        if(ret[id]=='0') id--;
        else{
            break;
        }
    }
    
    if(!has_dot) return ret;
    return ret.substr(0,id+1);

}


}

#endif // UTILS_H
