
#ifndef ARMATURE_H
#define ARMATURE_H


#include <QVariant>

#include "utils/Vec3.h"
#include "utils/Vec2.h"
#include "utils/Utils.h"

namespace solar
{

enum ArmatureType
{
    kOneAxis,
    kTwoAxis,
    kTwoAxisWithDrives
};

class Armature
{
public:
    Armature();
    virtual void setPara(const int property_type, const QVariant& value)=0;
    virtual auto getPara(const int property_type) const -> QVariant =0 ;
    virtual ArmatureType getType()const =0;
};







} // namespace solar
#endif // ARMATURE_H
