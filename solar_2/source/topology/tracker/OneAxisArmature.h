
#include "topology/tracker/Armature.h"

#include <QVariant>

#include "utils/Vec3.h"
#include "utils/Vec2.h"
#include "utils/Utils.h"

namespace solar{

class OneAxisArmature : public Armature
{
public:
    OneAxisArmature();

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

}