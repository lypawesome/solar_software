#include "topology/material/Absorb.h"
#include "utils/ParaUtils.h"

using namespace solar;

void solar::Absorb::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Absorb::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

auto solar::Absorb::getType() const -> MaterialType { return this->type_; }

void solar::Absorb::testPrint() const
{

}

