
#include "topology/geometry/MultiPanelComprisedOfHeatTube.h"

#include <utils/ParaUtils.h>

using namespace solar;


void solar::MultiPanelComprisedOfHeatTube::setPara(const std::string& property_type, const QVariant& value) 
{
    ::solar::setPara(property_type, value, this);
}
auto solar::MultiPanelComprisedOfHeatTube::getPara(const std::string& property_type) -> QVariant 
{
    return ::solar::getPara(property_type, this);

}

