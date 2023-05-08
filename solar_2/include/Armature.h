
#ifndef ARMATURE_H
#define ARMATURE_H


#include <QVariant>

#include "Vec3.h"
#include "Vec2.h"
#include "Utils.h"

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

class OneAxis : public Armature
{
public:
    OneAxis();

    void setPara(const int property_type, const QVariant& value) override ;
    auto getPara(const int property_type) const -> QVariant override;
    ArmatureType getType()const override
    {return type_;}

private:
    Vec3 primary_shift_;
    Vec3 primary_axis_;
    Vec2 primary_angles_;       //角度为啥是两个分量？？？
    Vec3 facet_shift_;
    Vec3 facet_normal_;
    Vec2 angle_default_;

    ArmatureType type_;
};

class TwoAxis : public Armature
{
public:
    TwoAxis();

    void setPara(const int property_type, const QVariant& value) override ;
    auto getPara(const int property_type) const -> QVariant override;
    ArmatureType getType()const override
    {return type_;}
private:
    Vec3 primary_shift_ ;
    Vec3 primary_axis_ ;
    Vec2 primary_angles_ ;
    Vec3 secondary_shift_ ;
    Vec3 secondary_axis_ ;
    Vec2 secondary_angles_ ;
    Vec3 facet_shift_ ;
    Vec3 facet_normal_ ;
    Vec2 angle_default_ ;

    ArmatureType type_;
};

class TwoAxisWithDrives : Armature
{
public:
    TwoAxisWithDrives();

    void setPara(const int property_type, const QVariant& value) override ;
    auto getPara(const int property_type) const -> QVariant override;
    ArmatureType getType()const override
    {return type_;}
private:
    Vec3 primary_shift_ ;
    Vec3 primary_axis_ ;
    Vec2 primary_angles_ ;
    Vec3 secondary_shift_ ;
    Vec3 secondary_axis_ ;
    Vec2 secondary_angles_ ;
    Vec3 facet_shift_ ;
    Vec3 facet_normal_ ;
    Vec2 angle_default_ ;
    Vec3 drive_primary_r_;
    Vec3 drive_primary_p_;
    Vec3 drive_secondary_p_;
    Vec3 drive_secondary_s_;

    ArmatureType type_;
};


} // namespace solar
#endif // ARMATURE_H
