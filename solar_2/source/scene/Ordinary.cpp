#include "scene/Ordinary.h"
#include "topology/geometry/Cylinder.h"
#include <utils/ParaUtils.h>

using namespace solar;

solar::Ordinary::Ordinary()
{
    geometry_ = std::make_shared<Cylinder>();
}

void solar::Ordinary::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Ordinary::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
void solar::Ordinary::testPrint() const
{

}