#include "topology/material/Reflect.h"
#include "utils/ParaUtils.h"

using namespace solar;

void solar::Reflect::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Reflect::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

auto solar::Reflect::getType() const -> MaterialType { return this->type_; }

void solar::Reflect::testPrint() const
{

}