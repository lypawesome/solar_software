
#include "utils/Utils.h"

namespace solar{

    auto Vec2::vec2ToString() -> std::string
    {
        return double2String(x()) + "," + double2String(y());
    }
}

