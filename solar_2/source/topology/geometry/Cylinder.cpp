#include "topology/geometry/Cylinder.h"
#include <utils/ParaUtils.h>

using namespace solar;

void solar::Cylinder::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Cylinder::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
