#include <format>
#include <iostream>

auto main() -> int
{
    std::cout << std::format("Test format {}", "c++20") << "\n";

    return 0;
}
