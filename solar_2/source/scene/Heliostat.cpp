#include "scene/Heliostat.h"
#include <memory>
#include <utils/ParaUtils.h>
#include "topology/geometry/Rectangle.h"
#include "topology/geometry/Geometry.h"
#include "topology/material/Material.h"
#include "topology/material/Refract.h"

using namespace solar;

int Heliostat::heliostat_cnt_ = 0;  //类的静态成员变量需要在类外分配空间


solar::Heliostat::Heliostat()
{
    id_ = -1;
    geometry_ = std::make_shared<Rectangle>();
    material_ = std::make_shared<Refract>();
}

void solar::Heliostat::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}

auto solar::Heliostat::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}

void solar::Heliostat::testPrint() const
{

}
