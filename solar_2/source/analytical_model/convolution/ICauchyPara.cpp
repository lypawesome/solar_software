#include <analytical_model/convolution/ICauchyPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::ICauchyPara::setPara(const std::string& property_type, const std::any& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::ICauchyPara::getPara(const std::string& property_type) -> std::any
{
    return ::solar::getParaAsAny(property_type, this);
}
