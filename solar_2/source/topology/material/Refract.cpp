#include "topology/material/Refract.h"
#include "utils/ParaUtils.h"

using namespace solar;

void solar::Refract::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Refract::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

auto solar::Refract::getType() const -> MaterialType { return this->type_; }

void solar::Refract::testPrint() const
{

}