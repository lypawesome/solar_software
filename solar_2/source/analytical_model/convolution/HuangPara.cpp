#include <analytical_model/convolution/HuangPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::HuangPara::setPara(const std::string& property_type, const std::any& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::HuangPara::getPara(const std::string& property_type) -> std::any
{
    return ::solar::getParaAsAny(property_type, this);
}
