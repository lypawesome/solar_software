
#include "topology/tracker/Target.h"
#include <utils/ParaUtils.h>

using namespace solar;

void solar::Target::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Target::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
