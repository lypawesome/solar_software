#pragma once

#include <concepts>
#include <type_traits>

namespace solar
{
    enum class ProjectionType
    {
        kParallel, // 斜平行投影
        kGnomonic, // 带投影校正的斜平行投影 [NEG]
    };

    enum class SimplifiedModelType
    {
        kHFLCAL,
        kiHFLCAL,
        kbHFLCAL,
        kNEG,
    };

    enum class ConvolutionModelType
    {
        kUNIZAR,
        kCauchy,
        kHuang,
    };
} // namespace solar
