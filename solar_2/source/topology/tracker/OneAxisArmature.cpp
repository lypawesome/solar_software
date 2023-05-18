
#include "topology/tracker/OneAxisArmature.h"

#include <utils/ParaUtils.h>

/*
    kPrimaryShift,
    kPrimaryAxis,
    kPrimaryAngles,

    kFacetShift,
    kFacetNormal,
    kAngleDefault,

*/

using namespace solar;

void solar::OneAxisArmature::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::OneAxisArmature::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
