#include <version>

auto main() -> int
{
#ifndef _MSVC_STL_VERSION
    #error "Not using MSVC STL"
#endif

    return 0;
}