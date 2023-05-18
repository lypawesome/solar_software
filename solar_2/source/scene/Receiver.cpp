#include "scene/Receiver.h"
#include <utils/ParaUtils.h>

using namespace solar;

void solar::Receiver::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Receiver::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
