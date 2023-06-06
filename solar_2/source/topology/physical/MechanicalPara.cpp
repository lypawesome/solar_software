#include "topology/physical/MechanicalPara.h"
#include "utils/ParaUtils.h"

using namespace solar;

void solar::MechanicalPara::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}
auto solar::MechanicalPara::getPara(const std::string& property_type) -> QVariant 
{
    return ::solar::getPara(property_type, this);
}