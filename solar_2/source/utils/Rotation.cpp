
#include "utils/Rotation.h"
#include <utils/ParaUtils.h>

#include <QDebug>

namespace solar
{

/*
    kAxis
    kAngle
*/

void Rotation::setPara(const std::string& property_type, const QVariant& value)
{
    ::solar::setPara(property_type, value, this);
}
auto Rotation::getPara(const std::string& property_type) -> QVariant
{
    return ::solar::getPara(property_type, this);
}
void Rotation::testPrint() const
{
   qDebug() << QString(::solar::format("\t Rotation::axis=({},{},{}), angle={}",
                           axis_.x(),axis_.y(), axis_.z(),angle_).c_str());
}

}   // namespace solar



