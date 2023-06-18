#include <analytical_model/HeliostatWithGlassPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::HeliostatWithGlassPara::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::HeliostatWithGlassPara::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::HeliostatWithGlassPara::testPrint() const {}