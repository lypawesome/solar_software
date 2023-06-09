
#include "utils/Utils.h"
#include <utils/Vec2.h>
#include <utils/Format.h>

namespace solar
{
    auto Vec2::toString() const -> std::string
    {
        return ::solar::format("{}, {}", this->e[0], this->e[1]);
    }
} // namespace solar
