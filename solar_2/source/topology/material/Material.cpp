
#include "Material.h"
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

void solar::Reflect::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Reflect::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

auto solar::Reflect::getType() const -> MaterialType { return this->type_; }

void solar::Refract::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Refract::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

auto solar::Refract::getType() const -> MaterialType { return this->type_; }
