
#include "topology/tracker/TwoAxisArmature.h"
#include <utils/ParaUtils.h>
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

using namespace solar;

void solar::TwoAxisArmature::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::TwoAxisArmature::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
