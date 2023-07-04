#include <analytical_model/HeliostatPara.h>
#include <analytical_model/HeliostatWithGlassPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

HeliostatPara::HeliostatPara()
{
    this->heliostat_glass_para_ = std::make_shared<HeliostatWithGlassPara>();
}

void solar::HeliostatPara::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::HeliostatPara::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::HeliostatPara::testPrint() const {}