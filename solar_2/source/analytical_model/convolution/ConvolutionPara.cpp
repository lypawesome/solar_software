#include <analytical_model/convolution/ConvolutionPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::ConvolutionPara::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::ConvolutionPara::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::ConvolutionPara::testPrint() const {}