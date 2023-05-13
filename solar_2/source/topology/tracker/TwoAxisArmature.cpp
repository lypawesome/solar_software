
#include "topology/tracker/TwoAxisArmature.h"
/*
    kPrimaryShift,
    kPrimaryAxis,
    kPrimaryAngles,
    kSecondaryShift,
    kSecondaryAxis,
    kSecondaryAngles,
    kFacetShift,
    kFacetNormal,
    kAngleDefault,
*/

namespace solar{
void TwoAxisArmature::setPara(const int property_type, const QVariant& value)
{
    switch(property_type)
    {
    case kPrimaryShift:     primary_shift_ = value.value<Vec3>();   break;
    case kPrimaryAxis:      primary_axis_ = value.value<Vec3>();    break;
    case kPrimaryAngles:    primary_angles_ = value.value<Vec2>();  break;
    case kSecondaryShift:   secondary_shift_ = value.value<Vec3>();   break;
    case kSecondaryAxis:    secondary_axis_ = value.value<Vec3>();    break;
    case kSecondaryAngles:  secondary_angles_ = value.value<Vec2>();  break;
    case kFacetShift:       facet_shift_ = value.value<Vec3>();     break;
    case kFacetNormal:      facet_normal_ = value.value<Vec3>();    break;
    case kAngleDefault:     angle_default_ = value.value<Vec2>();   break;

    default:
        throw "ERROR::TwoAxis::setPara()::no such property_type: "
            +std::to_string(property_type);
        break;
    }
}
auto TwoAxisArmature::getPara(const int property_type) const -> QVariant
{
    QVariant ret;
    switch(property_type)
    {
    case kPrimaryShift:     ret = QVariant::fromValue(primary_shift_) ;   break;
    case kPrimaryAxis:      ret = QVariant::fromValue(primary_axis_) ;    break;
    case kPrimaryAngles:    ret = QVariant::fromValue(primary_angles_) ;  break;
    case kSecondaryShift:   ret = QVariant::fromValue(secondary_shift_) ;   break;
    case kSecondaryAxis:    ret = QVariant::fromValue(secondary_axis_) ;    break;
    case kSecondaryAngles:  ret = QVariant::fromValue(secondary_angles_) ;  break;
    case kFacetShift:       ret = QVariant::fromValue(facet_shift_) ;     break;
    case kFacetNormal:      ret = QVariant::fromValue(facet_normal_) ;    break;
    case kAngleDefault:     ret = QVariant::fromValue(angle_default_) ;   break;
    default:
        throw "ERROR::TwoAxis::setPara()::no such property_type: "
            +std::to_string(property_type);
        break;
    }
    return ret;
}

}