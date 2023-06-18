#include <analytical_model/ScenePara.h>
#include <utils/ParaUtils.h>

using namespace solar;

void solar::ScenePara::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::ScenePara::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::ScenePara::testPrint() const {}