#include <analytical_model/simplified/SimplifiedPara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::SimplifiedPara::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::SimplifiedPara::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::SimplifiedPara::testPrint() const {}