#include <version>

auto main() -> int
{
#ifndef _LIBCPP_STD_VER
    #error "Not using libc++"
#endif

    return 0;
}
