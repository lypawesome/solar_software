#include "scene/Receiver.h"
#include "topology/geometry/Rectangle.h"
#include "topology/material/Absorb.h"
#include <utils/ParaUtils.h>

using namespace solar;

int Receiver::receiver_cnt_ = 0;


solar::Receiver::Receiver()
{
    id_ = -1;
    geometry_ = std::shared_ptr<Geometry>(new Rectangle());
    material_ = std::shared_ptr<Material>(new Absorb());
}

void solar::Receiver::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Receiver::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
void solar::Receiver::testPrint() const
{

}
