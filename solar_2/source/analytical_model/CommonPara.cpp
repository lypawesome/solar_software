#include <analytical_model/CommonPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::CommonPara::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::CommonPara::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::CommonPara::testPrint() const {}
