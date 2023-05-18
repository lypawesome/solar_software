

#include "topology/tracker/TwoAxisWithDrivesArmature.h"
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
    kDrivePrimaryR,
    kDrivePrimaryP,
    kDriveSecondaryP,
    kDriveSecondaryS,
*/

using namespace solar;

void solar::TwoAxisWithDrivesArmature::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::TwoAxisWithDrivesArmature::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
