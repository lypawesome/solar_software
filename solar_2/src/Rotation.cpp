
#include "Rotation.h"
#include <format>
namespace solar
{

/*
    kAxis
    kAngle
*/

void Rotation::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kAxis:
    {
        axis_ = value.value<Vec3>();
        break;
    }
    case kAngle:
    {
        angle_ = value.toDouble();
        break;
    }
    default:
    {
        throw "ERROR::Rotation::setPara()::no such property_type";
        break;
    }
    }
}
auto Rotation::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kAxis:
    {
        ret = QVariant::fromValue(axis_);
        break;
    }
    case kAngle:
    {
        ret = angle_;
        break;
    }
    default:
    {
        throw "ERROR::Rotation::setPara()::no such property_type";
        break;
    }
    }
    return ret;
}
void Rotation::testPrint() const
{
    qDebug() <<std::format("\t Rotation::axis=({},{},{}), angle={}",
                            axis_.x(),axis_.y(), axis_.z(),angle_);
}

}   // namespace solar



