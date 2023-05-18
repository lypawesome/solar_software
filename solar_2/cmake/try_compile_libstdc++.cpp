#include <version>

auto main() -> int
{
#ifndef _GLIBCXX_VERSION_INCLUDED
    #error "Not using libstdc++"
#endif

    return 0;
}
