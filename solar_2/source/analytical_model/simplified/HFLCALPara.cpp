#include <analytical_model/simplified/HFLCALPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::HFLCALPara::setPara(const std::string& property_type, const std::any& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::HFLCALPara::getPara(const std::string& property_type) -> std::any
{
    return ::solar::getParaAsAny(property_type, this);
}
