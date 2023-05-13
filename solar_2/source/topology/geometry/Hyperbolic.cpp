#include "topology/geometry/Hyperbolic.h"

namespace solar
{
    /*
 * ===========================Hyperbolic==========================
*/
void Hyperbolic::setPara(const int property_type, const QVariant& value)
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
    case kC:
    {
        c_ = value.toDouble();
        break;
    }
    default:
    {
        throw "ERROR::Hyperbolic::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto Hyperbolic::getPara(const int property_type) const -> QVariant
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
    case kC:
    {
        ret = c_;
        break;
    }
    default:
    {
        throw "ERROR::Hyperbolic::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}
}