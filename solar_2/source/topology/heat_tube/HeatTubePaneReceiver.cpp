
#include "topology/heat_tube/HeatTubePaneReceiver.h"
#include <utils/ParaUtils.h>

using namespace solar;

void solar::HeatTubePaneReceiver::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::HeatTubePaneReceiver::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

