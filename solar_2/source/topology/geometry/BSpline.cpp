#include "topology/geometry/BSpline.h"

namespace solar
{
    

/*
 * ===========================BSpline==========================
*/
void BSpline::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kFile:
    {
        file_ = value.toString().toStdString();
        break;
    }
    default:
    {
        throw "ERROR::BSpline::setPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
}
auto BSpline::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kFile:
    {
        ret = QString::fromStdString(file_);
        break;
    }
    default:
    {
        throw "ERROR::BSpline::getPara()::no such property_type: "
            + std::to_string(property_type);
        break;
    }
    }
    return ret;
}
}