
#include "topology/tracker/Target.h"

namespace solar
{
/*
 *      kAimingType,        //Target的属性
        kAimingPoint
        kAngle
*/
void Target::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kAimingType:   aiming_type_ = value.toString().toStdString();  break;
    case kAimingPoint:  aiming_point_ = value.value<Vec3>();    break;
    case kAngle:        angles_ = value.value<Vec2>();  break;

    default:
        throw "ERROR::Target::setPara()::no such property type: "
            + std::to_string(property_type);
        break;
    }
}
auto Target::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kAimingType:   ret = QString::fromStdString(aiming_type_) ;  break;
    case kAimingPoint:  ret = QVariant::fromValue(aiming_point_) ;    break;
    case kAngle:        ret = QVariant::fromValue(angles_) ;  break;

    default:
        throw "ERROR::Target::setPara()::no such property type: "
            + std::to_string(property_type);
        break;
    }
    return ret;
}

} //namespace solar

