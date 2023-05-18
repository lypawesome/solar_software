#pragma once

#if HAVE_STD_FORMAT
    #include <format>
namespace solar
{
    using std::format;
}
#else
    #include <fmt/format.h>
namespace solar
{
    using fmt::format;
}
#endif
