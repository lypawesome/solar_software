
#include <utils/Format.h>
#include <utils/Vec2.h>

#include <boost/algorithm/string.hpp>

namespace solar
{
    auto Vec2::toString() const -> std::string
    {
        return ::solar::format("{}, {}", this->e[0], this->e[1]);
    }

    auto Vec2::fromString(const std::string& input) -> Vec2
    {
        std::vector<std::string> split_strings;
        boost::split(split_strings, input, boost::is_any_of(" ,"), boost::token_compress_on);
        return {
            std::stod(split_strings[0]),
            std::stod(split_strings[1]),
        };
    }
} // namespace solar
