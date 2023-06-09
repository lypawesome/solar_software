#include <analytical_model/simplified/BHFLCALPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::BHFLCALPara::setPara(const std::string& property_type, const std::any& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::BHFLCALPara::getPara(const std::string& property_type) -> std::any
{
    return ::solar::getParaAsAny(property_type, this);
}
