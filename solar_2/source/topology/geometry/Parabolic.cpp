#include "topology/geometry/Parabolic.h"

namespace solar
{
    /*
 * ==========================Parabolic================================
 * kA, kB
*/
void Parabolic::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kA:
    {
        a_ = value.toDouble();
        break;
    }
    case kB:
    {
        b_ = value.toDouble();
        break;
    }
    default:
    {
        throw "ERROR::Parabolic::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto Parabolic::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kA:
    {
        ret = a_;
        break;
    }
    case kB:
    {
        ret = b_;
        break;
    }
    default:
    {
        throw "ERROR::Parabolic::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}
}