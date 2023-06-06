#include "topology/geometry/Hyperbolic.h"
#include <utils/ParaUtils.h>

using namespace solar;



void solar::Hyperbolic::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Hyperbolic::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
