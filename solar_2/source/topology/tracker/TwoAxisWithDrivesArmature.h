
#include "topology/tracker/Armature.h"

#include <QVariant>

#include "utils/Vec3.h"
#include "utils/Vec2.h"
#include "utils/Utils.h"


namespace solar{


class TwoAxisWithDrivesArmature : Armature
{
public:
    TwoAxisWithDrivesArmature();

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

}